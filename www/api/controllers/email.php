<?
require_once '../common.php';

/////////////////////////////////////////////////////////////////////////////
function ConfigureEmail() {
    $result = Array();

    ApplyEmailConfig();

    $result['Status'] = 'OK';
    $result['Message'] = '';

    return json($result);
}

/////////////////////////////////////////////////////////////////////////////
function SendTestEmail() {
    global $settings;
    $result = Array();

    system('echo "Email test from $(hostname)" | mail -s "Email test from $(hostname)" ' . $settings['emailtoemail']);

    $result['Status'] = 'OK';
    $result['Message'] = '';

    return json($result);
}

/////////////////////////////////////////////////////////////////////////////

?>
