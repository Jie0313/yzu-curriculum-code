<?php

require_once('../TCPDF/tcpdf_import.php');

/*---------------- Sent Mail Start -----------------*/
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

require_once('Exception.php');
require_once('PHPMailer.php');
require_once('SMTP.php');
mb_internal_encoding('UTF-8');
$name = $_POST['name'];
$cellphone = $_POST['cellphone'];
$email = $_POST['email'];
$Path = 'qrcode.png';
$money = $_POST['money'];
$method = $_POST['method'];
$mail = new PHPMailer();
$mail->IsSMTP();
$mail->SMTPAuth = true;
$mail->SMTPSecure = "ssl";
$mail->Host = "smtp.gmail.com";
$mail->Port = 465;
$mail->CharSet = 'UTF-8';

$mail->Username = "lshijie203@gmail.com";
$mail->Password = "mnwt pmqo wnux lmip";

$mail->From = "lshijie203@gmail.com";
$mail->FromName = "1133348 羅世捷";

$mail->Subject = "捐款單確認信";
$mail->Body = "<h1>感謝您的支持!</h1><br>姓名: $name<br>電話: $cellphone<br>捐款金額: $money<br>電子郵件: $email<br>捐款方式: $method";
$mail->IsHTML(true);
$mail->AddAddress($email);
$mail->addAttachment($Path); // 只提供文件路径，默认会使用文件名作为附件名

if (!$mail->send()) {
	echo "Mailer Error: " . $mail->ErrorInfo;
}
/*---------------- Sent Mail End -------------------*/

/*---------------- Print PDF Start -----------------*/
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('cid0jp','', 18); 
$pdf->AddPage();


$html = <<<EOF
<h1>捐款單</h1>
<table border="2">
<tr>
	<td>姓名: $name</td>
	<td>電話: $cellphone</td>
	<td style="color:red;">捐款金額: $money</td>
</tr>
<tr>
	<td colspan="3">電子郵件: $email</td>
</tr>
<tr>
	<td colspan="3">捐款方式: $method</td>
</tr>
</table>
<h2>感謝您的支持</h2>
EOF;
/*---------------- Print PDF End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('order.pdf', 'I');
