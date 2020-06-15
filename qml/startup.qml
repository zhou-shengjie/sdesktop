import QtQuick 2.14
import QtQuick.Dialogs 1.3
import Sjyun.Desktop 1.0

Item{
    MessageDialog {
        id: messageDialog
        title: "错误"
        text: "无法加载配置文件"
        standardButtons: StandardButton.Ok
        onAccepted: {
            console.log("无法加载配置文件")
            Qt.quit()
        }
    }

    Component.onCompleted: {
        //  载入config
        var isOk = GlobalConfig.loadConfig();
        if (isOk === false) {
            messageDialog.visible = true;
        }   else {
            var host;
            host = GlobalConfig.getString("host");
            HttpClientMgr.setHost(host);
            var loginComp = Qt.createComponent("qrc:/qml/login.qml");
            var loginWindow = loginComp.createObject();
        }
    }
}
