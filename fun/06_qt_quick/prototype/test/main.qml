import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import ".."

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    LoginPage {
//        visible: false
        id : login
        anchors.fill: parent
        onLoggedIn: {
            login.visible = false
            request.visible = true
        }
    }
    RequestPage {
        visible: false
        id: request
        anchors.fill: parent
    }

}
