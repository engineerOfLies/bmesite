<?php

require_once("err.inc");
/**
	@brief used for web php to validate a session information from a request
	@param session Mixed, expected to have name and id of the session to validate
*/
function validateSession($session)
{
	$session = json_decode($session);
	if (!isset($session))
	{
		err("no session information provided");	
	}
	file_put_contents("/tmp/phpoutput",print_r($session,true),FILE_APPEND);
	$auth = new AuthDB();
	$sessionId = $session->id;
	$name = $session->name;
	$valid = $auth->validateSession($name,$sessionId);
	if ($valid["status"] != "success")
	{
		err("session validation error: ".print_r($valid["status"],true));
	}
	return "ok";
}

class AuthDB
{
	private $db;

	public function __construct($confFile = "/var/www/ini/dbaccess.ini")
	{
		$conf = parse_ini_file($confFile,false);
		$this->db = new mysqli("localhost",$conf["username"],$conf["password"],$conf["db"]);
		$this->salt = $conf['salt'];
		$this->timeout = $conf['timeout'];
		if ($this->db->errno != 0)
		{
			echo "failed to connect to the database: ".$this->db->error.PHP_EOL;
		}
	}
	public function __destruct()
	{
		$this->db->close();
	}

	private function saltPassword($password)
	{
		return hash("sha256",$this->salt.$password);
	}

	public function register($username,$password,$email)
	{
		return $this->registerUser($username,$password,"p",$email);
	}

	public function registerUser($username,$password,$role,$email)
	{
		$un = $this->db->real_escape_string($username);
		$pw = $this->db->real_escape_string($this->saltPassword($password));
		$r = trim(strtolower($role));
		$em = $this->db->real_escape_string($email);
		switch($r)
		{
			case "player":
			case "p":
				$ur = "p";
				break;
			case "administrator":
			case "admin":
				$ur = "ad";
				break;
			default:
				return array(
					"status"=>"fail",
					"message"=>"unsupported user role");
				break;
		}
		$query = "select * from auth where username = '$un' or email = '$em';";
		$result = $this->db->query($query);
		if ($result->num_rows != 0)
		{
			return array(
					"status"=>"fail",
					"message"=>"username or password already in use");
		}
		$insert = "insert into auth (username,password,role,email) values ('$un','$pw','$ur','$em');";
		$result = $this->db->query($insert);
		if ($this->db->affected_rows != 1)
		{
			echo "error: failed to insert row with query:".PHP_EOL;
			echo $insert.PHP_EOL;
			return array(
					"status"=>"fail",
					"message"=>"failed to insert row");	
		}
		return array(
			"status"=>"success");
	}
	
	public function validateUser($username, $password)
	{
		$un = $this->db->real_escape_string($username);
		$pw = $this->db->real_escape_string($this->saltPassword($password));
		$query = "select * from auth where username = '$un';";
		$result = $this->db->query($query);
		while ($row = $result->fetch_assoc())
		{
			if (($row['username'] == $un) && ($row['password'] == $pw))
			{
				return array(
					"status"=>"success",
					"userId"=> $row['userId'],
					"role"=> $row['role']);
			}
		}
		return array(
				"status"=>"fail");	
	}

	private function getIdByUsername($username)
	{
		$un = $this->db->real_escape_string($username);
		$query = "select username from auth where username = '".$un."';";
		$result = $this->db->query($query);
		while ($row = $result->fetch_assoc())
		{
			return $row["userId"];
		}
		return NULL;
	}

	public function userLogin($username, $password)
	{
		$result = $this->validateUser($username,$password);
		if ($result["status"] != "success")
		{
			return $result;
		}
		$sessionId = sha1(time()+$this->salt+$result['userId']);
		//invalidate all other sessions for this user
		$invalidate = "update sessions set invalid = 1 where userId = '".$result['userId']."';";
		$this->db->query($invalidate);
		//new session ID for this user
		$query = "insert into sessions (sessionString,userId,timestamp,invalid) values ('$sessionId',".$result['userId'].",".time().",0);";
		$this->db->query($query);
		if ($this->db->affected_rows != 1)
		{
			echo "error: failed to insert row with query:".PHP_EOL;
			echo $query.PHP_EOL;
			return array(
					"status"=>"fail",
					"message"=>"failed to insert row");	
		}
		return array(
			"status"=>"success",
			"username"=>$username,
			"role"=>$result["role"],
			"sessionId"=>$sessionId
		);
	}

	public function validateSession($username,$sessionId)
	{
		$un = $this->db->real_escape_string($username);
		$si = $this->db->real_escape_string($sessionId);

		$sessionQuery = "select timestamp,invalid from sessions,auth where auth.userId = sessions.userId and sessions.sessionString = '$si'";
		$result = $this->db->query($sessionQuery);
		while ($row = $result->fetch_assoc())
		{
			if ($row["invalid"] == 1)
			{
				return array(
						"status"=>"fail: session expired");
			}
			if ($row["timestamp"] < (time() - $this->timeout))
			{
				return array(
						"status"=>"timeout");
			}
			$update = "update sessions set timestamp = ".time()." where sessionString = '$si';";
			file_put_contents("/tmp/phperr.log",$update.PHP_EOL,FILE_APPEND);
			$result = $this->db->query($update);
			if ($this->db->errno != 0)
			{
				echo "error: failed to insert session row with query:".PHP_EOL;
				echo $update.PHP_EOL;
				return array(
						"status"=>"fail: failed to update Session timestamp: ".$this->db->error,
						"message"=>"failed to insert row");	
			}
			return array(
				"status"=>"success"
			);	
		}
		return array(
			"status"=>"unknown session");
	}
}

?>

