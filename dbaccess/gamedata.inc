<?php
require_once("err.inc");

class GameDataDB
{
	private $db;

	public function __construct($confFile = "/var/www/ini/gameDataAccess.ini")
	{
		$conf = parse_ini_file($confFile,false);
		$this->db = new mysqli("localhost",$conf["username"],$conf["password"],$conf["db"]);
		if ($this->db->errno != 0)
		{
			echo "failed to connect to the database: ".$this->db->error.PHP_EOL;
		}
	}
	public function __destruct()
	{
		$this->db->close();
	}

	private function err($msg)
	{
		return array(
			"status"=>"error",
			"message"=> "GameDataDB: $msg"
		);
	}

	public function getGameIdByName($name)
	{
		$un = $this->db->real_escape_string($name);
		$query = "select gameId from gameTable where name like '%$name%';";
		$result = $this->db->query($query);
		$id = NULL;
		while ($row = $result->fetch_assoc())
		{
			$id = $row["gameId"];
		}
		return $id;
	}

	public function getGameInformationById($gameId)
	{
		$gameId = $this->db->real_escape_string($gameId);
		$query = "select * from gameTable where gameId = $gameId;";
		$result = $this->db->query($query);
		while ($row = $result->fetch_assoc())
		{
			return $row;
		}
		return NULL;
	}

	public function getSessionData($gameSessionId)
	{
		$gsi = $this->db->real_escape_string($gameSessionId);
		$query = "select * from gameData where gameSessionId = $gsi;";
		echo "$query\n";
		$result = $this->db->query($query);
		if (!$result)
		{
			return array("status"=>"fail","message"=>"failed to extract data: ".$this->db->error.PHP_EOL);
		}
		$results = array();
		while ($row = $result->fetch_assoc())
		{
			$results[] = $row;
		}
		return $results;
	}

	public function getSessionList($gameName)
	{
		$gn = $this->getGameIdByName($gameName);
		$query = "select gameSessionId,gameId,startTime,endtime from gameSessions where gameId = $gn;";
		echo "$query\n";
		$result = $this->db->query($query);
		if (!$result)
		{
			return array("status"=>"fail","message"=>"failed to extract data: ".$this->db->error.PHP_EOL);
		}
		$results = array();
		while ($row = $result->fetch_assoc())
		{
			$row["gameName"] = $gameName;
			$results[] = $row;
		}
		return $results;
	}

	public function endGameSession($gameSessionId,$endTime,$custom)
	{
		$gsi = $this->db->real_escape_string($gameSessionId);
		$query = "update gameSessions set entTime = $endTime where gameSessionId = $gsi;";
		if ($this->db->query($query) !== TRUE)
		{
			return array("status"=>"fail","message"=>"failed to end session: ".$this->db->error.PHP_EOL);
		}
		return array("status"=>"success");
	}

	public function startGameSessionName($gameName,$startTime,$patientId,$calibrations)
	{
		$gameId = $this->getGameIdByName($name);
		if ($gameId == NULL)
		{
			return $this->err("no game by known by $gameName");
		}
		return $this->startGameSession($gameId,$startTime,$patientId,$calibrations);
	}
	
	public function startGameSession($gameId,$startTime,$patientId,$calibrations)
	{
		$gameInfo = $this->getGameInformationById($gameId);
		if ($gameInfo == NULL)
		{
			return array("status"=>"fail","message"=>"no game with id $gameId");
		}
		$squery = "insert into gameSessions (gameId,patientId,startTime,endTime,therapistPresent) values($gameId,$patientId,$startTime,NULL,false);";
		if ($this->db->query($squery) !== TRUE)
		{
			return array("status"=>"fail","message"=>"failed to insert session: ".$this->db->error.PHP_EOL);
		}
		$gameSessionId = $this->db->insert_id;
		$tableName = $gameInfo["customSessionTable"];
		if (is_string($tableName) && (strlen($tableName > 1)))
		{
			/*insert the game specific session data*/
			$columns = "";
			$values = "";
			foreach ($calibrations as $column => $value)
			{
				$columns .= $column.",";
				$values .= $value.",";
			}
			$columns .= "gameSessionId";
			$values .= $gameSessionId;
			$gameSessionQuery = "insert into $tableName ($columns) values ($values);";
			if ($this->db->query($gameSessionQuery) !== TRUE)
			{
				return array("status"=>"fail","message"=>"failed to insert session");	
			}
		}
		return array("gameSessionId"=>$gameSessionId,"gameId"=>$gameId);
	}

	public function recordGameState($sessionId,$orientations,$custom)
	{
		$insert = "insert into gameData (gameSessionId,timestamp,handPalmX,handPalmY,handPalmZ,palmNormalX,palmNormalY,palmNormalZ,wristPositionX,wristPositionY,wristPositionZ,thumbMetacarpalX,thumbMetacarpalY,thumbMetacarpalZ,thumbProximalX,thumbProximalY,thumbProximalZ,thumbIntermediateX,thumbIntermediateY,thumbIntermediateZ,thumbDistalX,thumbDistalY,thumbDistalZ,thumbTipX,thumbTipY,thumbTipZ,indexMetacarpalX,indexMetacarpalY,indexMetacarpalZ,indexProximalX,indexProximalY,indexProximalZ,indexIntermediateX,indexIntermediateY,indexIntermediateZ,indexDistalX,indexDistalY,indexDistalZ,indexTipX,indexTipY,indexTipZ,middleMetacarpalX,middleMetacarpalY,middleMetacarpalZ,middleProximalX,middleProximalY,middleProximalZ,middleIntermediateX,middleIntermediateY,middleIntermediateZ,middleDistalX,middleDistalY,middleDistalZ,middleTipX,middleTipY,middleTipZ,ringMetacarpalX,ringMetacarpalY,ringMetacarpalZ,ringProximalX,ringProximalY,ringProximalZ,ringIntermediateX,ringIntermediateY,ringIntermediateZ,ringDistalX,ringDistalY,ringDistalZ,ringTipX,ringTipY,ringTipZ,pinkyMetacarpalX,pinkyMetacarpalY,pinkyMetacarpalZ,pinkyProximalX,pinkyProximalY,pinkyProximalZ,pinkyIntermediateX,pinkyIntermediateY,pinkyIntermediateZ,pinkyDistalX,pinkyDistalY,pinkyDistalZ,pinkyTipX,pinkyTipY,pinkyTipZ) Values ";
		foreach ($orientations as $index => $ori)
		{
			if ($index != "0")
			{
				$insert .= ",";
			}
			$insert .= "($sessionId";
			foreach ($ori as $i => $value)
			{
				$insert .= ",$value";
			}
			$insert .= ")";
		}
		$insert .= ";";	
		if ($this->db->query($insert) !== TRUE)
		{
			err("db error: ".$this->db->error);	
		}
		return array ("status"=>"ok");
	}
}
?>
