<?
header( "Access-Control-Allow-Origin: *");

$wrapped = 0;

if (isset($_GET['wrapped']))
    $wrapped = 1;

if (!$wrapped)
    echo "<html>\n";

$skipJSsettings = 1;
require_once("common.php");

DisableOutputBuffering();

if (!$wrapped) {
?>
<head>
<title>
FPP Manual Update
</title>
</head>
<body>
<h2>FPP Manual Update</h2>
<pre>
<?
}
?>
Pulling in updates...
<?
system("$fppDir/scripts/git_pull");
?>
==========================================================================
Restarting fppd...
<?
touch("$mediaDirectory/tmp/fppd_restarted");

system($SUDO . " $fppDir/scripts/fppd_restart");

if (file_exists($settings['statsFile'])) {
    unlink($settings['statsFile']);
}
 
exec($SUDO . " rm -f /tmp/cache_*.cache");
?>
==========================================================================
Update Complete.
<?
if (!$wrapped) {
?>
<a href='index.php'>Go to FPP Main Status Page</a><br>
<a href='about.php'>Go back to FPP About page</a><br>

</body>
</html>
<?
}
?>
