	<footer>
	<script src="https://code.jquery.com/jquery-3.1.1.slim.min.js" integrity="sha384-A7FZj7v+d/sdmMqp/nOQwliLvUsJfDHW+k9Omg/a/EheAdgtzNs3hpfag6Ed950n" crossorigin="anonymous"></script>
    <script>window.jQuery || document.write('<script src="js/vendor/jquery.min.js"><\/script>')</script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js" integrity="sha384-DztdAPBWPRXSA/3eYEEUWrWCy7G5KFbe8fFjk5JAIxUYHKkDx6Qin1DkWx51bBrb" crossorigin="anonymous"></script>
    <script src="js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="js/ie10-viewport-bug-workaround.js"></script>

    <!-- local project includes -->
    <script src="js/hovrs/calls.js"></script>
	<script>
	/*	document.onload = function()*/
	if (typeof sessionStorage.sessionId !== 'undefined')
	{
		$("#profile").removeClass('disabled');
		$("#orientation").removeClass('disabled');
		$("#loginButton").text('logout');
		document.getElementById("loginButton").onclick = function() {location.reload();location.href='logout.php';};
	}
	// send session validation
	validateSession();
	</script>
	<div id="output">
	</div>
	</footer>

