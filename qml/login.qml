import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.0
import Sjyun.Desktop 1.0

Window {
    //  1.id
    id: loginWindow

    //  2.property declarations
    property Captcha captcha: Captcha {}
    property ErrMsg errMsg: ErrMsg{}
    property GetCaptchaResponse getCaptchaResp: GetCaptchaResponse {}

    //  3.signal declarations

    //  4.JavaScript functions
    function login() {

    }

    function refreshCaptcha() {
        var isOk = captcha.getCaptcha(HttpClientMgr, getCaptchaResp, errMsg);
        if (isOk === false) {
            return
        }
        ImageProviderBridge.addImage(getCaptchaResp.captchaId, getCaptchaResp.captchaImg);
        image_captcha.source = "image://imageProvider/" + getCaptchaResp.captchaId;
        ImageProviderBridge.deleteImage(getCaptchaResp.captchaId)
    }

    //  5.object properties
    visible: true
    width: 350
    height: 600

    title: qsTr("瞬捷云登录")
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    //  6.child objects
    Component.onCompleted: {
        //refreshCaptcha()
    }

    Connections {
        target: mouseArea_captcha
        onClicked: {
            refreshCaptcha()
        }
    }

    Connections {
        target: button_login
        onClicked: {
            var component = Qt.createComponent("qrc:/qml/userinfo.qml");
            var window    = component.createObject();
            window.show()
        }
    }

    Image {
        id: image_loginBg
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        opacity: 0.6
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "../pic/loginBg.jpg"
    }

    Column {
        id: column_login
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent
        spacing: 20

        Image {
            id: image_logo
            width: 150
            height: 150
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 100
            source: "../pic/cloud.png"
            fillMode: Image.PreserveAspectCrop
        }

        Text {
            id: text_title
            color: "#000000"
            text: qsTr("瞬捷云")
            font.strikeout: false
            font.underline: false
            font.italic: false
            font.bold: false
            font.family: "Microsoft YaHei"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 35
        }

        TextField {
            id: textField_account
            width: parent.width - 60
            font.family: "Microsoft YaHei"
            placeholderText: qsTr("账号")
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.fillWidth: true
        }

        TextField {
            id: textField_passwd
            width: parent.width - 60
            height: 40
            echoMode: TextInput.Password
            font.family: "Microsoft YaHei"
            placeholderText: qsTr("密码")
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.fillWidth: true
        }

        Row {
            id: row_captcha
            width: 290
            height: 56
            spacing: 5
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter

            TextField {
                id: textField_captcha
                width: 110
                anchors.verticalCenter: parent.verticalCenter
                placeholderText: qsTr("验证码")
                font.family: "Microsoft YaHei"
            }

            Rectangle {
                id: rectangle
                width: 168
                height: 56
                color: "#ffffff"

                Image {
                    id: image_captcha
                    anchors.fill: parent
                    sourceSize.height: 80
                    sourceSize.width: 240
                    clip: false
                    fillMode: Image.PreserveAspectFit
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

        }

        Button {
            id: button_login
            width: parent.width - 60
            text: qsTr("登录")
            font.family: "Microsoft YaHei"
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

    }

    ColumnLayout {
        id: buttom
        x: 0
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        Text {
            id: text_slogan
            width: 96
            height: 8
            color: "#ffffff"
            text: qsTr("CopyLeft©2020-？")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: "Microsoft YaHei"
            font.pixelSize: 12
        }

        Text {
            id: text_copyleft
            width: 96
            height: 8
            color: "#ffffff"
            text: qsTr("自由探索欢乐的云")
            font.family: "Microsoft YaHei"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 12
        }

    }

    //  7.states

    //  8.transitions

}
