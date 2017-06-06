#!/usr/bin/php
<?php
require_once("gamedata.inc");


function displayHelp()
{
	global $argv;
	echo "usage:\n";
	echo $argv[0]." -a [startsession,endsession,getsessiondata] -u <patientid> -g <gamename> -s <sessionId> -t <timestamp> -c <calibrations>\n";
	exit(0);
}

for($i = 1;$i < $argc;$i++)
{
	switch($argv[$i])
	{
		case "-a":
			$i++;
			$action = $argv[$i];
		break;
		case "-u":
			$i++;
			$username = $argv[$i];
		break;
		case "-g":
			$i++;
			$game = $argv[$i];
		break;
		case "-t":
			$i++;
			$timestamp = $argv[$i];
		break;
		case "-s":
			$i++;
			$session = $argv[$i];
		break;
		case "-c":
			$i++;
			$calibrations = $argv[$i];
		break;
		default:
		case "-h":
		case "--help":
			displayHelp();
		break;
	}
}
if (!isset($action))
{
	displayHelp();
}

switch($action)
{
	case "startsession":
		if ((!isset($username)) || (!isset($timestamp)) || (!isset($game)) || (!isset($calibrations)))
		{
			displayHelp();
		}
		$db = new GameDataDB();
		$response = $db->startGameSessionName($game,$timestamp,$username,$calibrations);
		echo "response:\n";
		print_r($response);
		echo "\n";
		exit (0);
		break;
	case "endsession":
		if ((!isset($timestamp)) || (!isset($game)) || (!isset($calibrations)))
		{
			displayHelp();
		}
		$db = new GameDataDB();
		$response = $db->startGameSessionName($game,$timestamp,$calibrations);
		echo "response:\n";
		print_r($response);
		echo "\n";
		exit (0);
		break;
	case "getsessionlist":
		if  (!isset($game))
		{
			displayHelp();
		}
		$db = new GameDataDB();
		$response = $db->getSessionList($game);
		echo "response:\n";
		print_r($response);
		echo "\n";
		exit (0);
		break;
	case "getsessiondata":
		if  (!isset($game))
		{
			displayHelp();
		}
		$db = new GameDataDB();
		$response = $db->getSessionData($game);
		echo "response:\n";
		print_r($response);
		echo "\n";
		exit (0);
		break;
	default:
		displayHelp();
		break;
}

?>

