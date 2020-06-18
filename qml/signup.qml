import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3
import Sjyun.Desktop 1.0

Window {
    //  1.id
    id: window_signup

    //  2.property declarations

    //  3.signal declarations

    //  4.JavaScript functions
    function refreshCaptcha() {
        var isOk = captcha.getCaptcha(HttpClientMgr, getCaptchaResp, errMsg);
        if (isOk === false) {
            messageDialog_getCaptchaFailed.text = errMsg.result
            messageDialog_getCaptchaFailed.detailedText = errMsg.errMsg
            messageDialog_getCaptchaFailed.open();
            return
        }
        ImageProviderBridge.addImage(getCaptchaResp.captchaId, getCaptchaResp.captchaImg);
        image_captcha.source = "image://imageProvider/" + getCaptchaResp.captchaId;
        ImageProviderBridge.deleteImage(getCaptchaResp.captchaId)
    }

    //  5.object properties
    width: 400
    height: 500
    title: qsTr("用户注册")

    //  6.child objects
    Connections {
        target: mouseArea_captcha
        onClicked: {
            refreshCaptcha()
        }
    }

    Connections {
        target: window_signup
        onClosing: function(close){
            window_signup.destroy()
        }
    }

    Column {
        id: column
        spacing: 15
        anchors.topMargin: 50
        anchors.fill: parent

        Text {
            id: text_signup
            text: qsTr("用户注册")
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 21
            font.family: "Microsoft Yahei"
        }

        GridLayout {
            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            columnSpacing: 15
            rows: 5
            columns: 2

            //  用户名
            Text {
                id: text_userName
                text: qsTr("用户名")
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
            }

            TextField {
                id: textField_text_userName
                font.pixelSize: 16
                font.family: "Microsoft Yahei"
                Layout.fillWidth: true
            }

            //  密码
            Text {
                id: text_password
                text: qsTr("密码")
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
            }

            TextField {
                id: textField_password
                font.family: "Microsoft Yahei"
                Layout.fillWidth: true
                font.pixelSize: 16
                echoMode: TextInput.Password
            }

            //  邮箱
            Text {
                id: text_email
                text: qsTr("邮箱")
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
            }

            TextField {
                id: textField_email
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
                Layout.fillWidth: true

            }

            //  手机
            Text {
                id: text_phone
                text: qsTr("手机")
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
            }

            TextField {
                id: textField_phone
                font.pixelSize: 16
                font.family: "Microsoft Yahei"
                Layout.fillWidth: true

            }

            //  性别
            Text {
                id: text_gender
                text: qsTr("性别")
                font.family: "Microsoft Yahei"
                font.pixelSize: 16
            }

            TextField {
                id: textField_gender
                font.pixelSize: 16
                font.family: "Microsoft Yahei"
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: rectangle_captcha
            width: 168
            height: 56
            color: "#ffffff"
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: image_captcha
                anchors.fill: parent
                sourceSize.height: 80
                sourceSize.width: 240
                clip: false
                fillMode: Image.Stretch
                source: "../pic/code.png"
            }

            MouseArea {
                id: mouseArea_captcha
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent
            }
        }

        Button {
            id: button_signup
            text: qsTr("注册")
            font.pixelSize: 16
            font.family: "Microsoft YaHei"
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

    MessageDialog {
        id: messageDialog_getCaptchaFailed
        title: qsTr("获取验证码失败")
        standardButtons: StandardButton.Ok
    }

    //  7.states
    //  8.transitions
}
