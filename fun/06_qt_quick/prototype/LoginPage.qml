import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property string cookie
    signal loggedIn()

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top

        TextField {
            id: loginText
            placeholderText: qsTr("login")
        }
        TextField {
            id: password
            echoMode: TextInput.Password
            placeholderText: qsTr("password")
        }
        Button {
            id: button1
            text: qsTr("Log In")
            onClicked: {
               var xmlHttp = new XMLHttpRequest();
               xmlHttp.onreadystatechange = function() {
                   if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                       var response = JSON.parse(xmlHttp.responseText)
                       cookie = response.session.value
                       loggedIn()
                   }
               }
               xmlHttp.open("POST", "https://jira.autodesk.com/rest/auth/1/session", true); // true for asynchronous
               xmlHttp.setRequestHeader("Content-type", "application/json");
               var data = {"username":loginText.text, "password":password.text}
               xmlHttp.send(JSON.stringify(data));
            }
        }
    }
}

