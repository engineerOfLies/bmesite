<?php
/**
	@brief used to send an error to the front end
*/
function err($msg)
{
	file_put_contents("/tmp/phperr.log",$msg."\n",FILE_APPEND);
    echo json_encode(array(
        "status"=>"error",
        "message"=> "$msg"
    ));
	exit(0);
}
?>
