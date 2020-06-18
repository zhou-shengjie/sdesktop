import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.0
import Sjyun.Desktop 1.0

Window {
    //  1.id
    id: window_userInfo

    //  2.property declarations
    property UserInfo userInfo: null
    //  3.signal declarations

    //  4.JavaScript functions

    //  6.child objects
    Connections {
        target: window_userInfo
        onClosing: function(close) {
            window_userInfo.destroy()
        }
    }

    Item {
        id: item_userInfo
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 30
        anchors.fill: parent

        Column {
            id: col
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            spacing: 10
            anchors.fill: parent

            Image {
                id: image
                width: 150
                height: 150
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                source: userInfo.avatar
            }

            GridLayout {
                width: 317
                height: 274
                columnSpacing: 15
                anchors.horizontalCenter: parent.horizontalCenter
                rows: 5
                columns: 2

                //  用户id
                Text {
                    id: text_userId
                    text: qsTr("用户id")
                    font.family: "Microsoft Yahei"
                    font.pixelSize: 16
                }

                TextField {
                    id: textField_userId
                    text: userInfo.userId
                    font.family: "Microsoft Yahei"
                    Layout.fillWidth: true
                    font.pixelSize: 16
                }

                //  用户名
                Text {
                    id: text_userName
                    text: qsTr("用户名")
                    font.family: "Microsoft Yahei"
                    font.pixelSize: 16
                }

                TextField {
                    id: textField_text_userName
                    text: userInfo.userName
                    font.pixelSize: 16
                    font.family: "Microsoft Yahei"
                    Layout.fillWidth: true
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
                    text: userInfo.mail
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
                    text: userInfo.phone
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
                    text: userInfo.gender
                    font.pixelSize: 16
                    font.family: "Microsoft Yahei"
                    Layout.fillWidth: true
                }
            }
        }
    }

    //  5.object properties
    width: 400
    height: 500
    title: qsTr("用户信息")
    //  7.states

    //  8.transitions
}
