import bb.cascades 1.0

Page { 
    property alias sdcard: sdcard.checked
    property alias boxartEnabled: boxart.checked
    property bool helpEnabled: false
    
    titleBar: TitleBar {
        id: titleBar3
        title: "General Settings"
        visibility:  ChromeVisibility.Visible
        scrollBehavior: TitleBarScrollBehavior.Sticky
    }
    
    actions: [
        ActionItem {
            
            id: help
            title: {
                if(helpEnabled){
                    "Hide Help"
                } else {
                    "Show Help"
                }
            }
            imageSource: "asset:///images/ic_help.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                if(!helpEnabled)
                    helpEnabled = true;
                else
                    helpEnabled = false;
            }
        }
    ]
    
    ScrollView {
	    Container{
	        topPadding: 20
	        leftPadding: 20
	        rightPadding: 20
	        
	        Container {
	            horizontalAlignment: HorizontalAlignment.Center
	            preferredWidth: 768
	            
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }
	        
	            Label {
	                horizontalAlignment: HorizontalAlignment.Left
	                verticalAlignment: VerticalAlignment.Center
	                preferredWidth: 768
	                text: "Default to SD Card"
	            }
	            
	            ToggleButton {
	                id: sdcard
	                checked: _frontend.getValueFor(objectName, "false")
	                objectName: "sdcard"
	                horizontalAlignment: HorizontalAlignment.Right
	                onCheckedChanged: {
	                    _frontend.saveValueFor(sdcard.objectName, checked)
	                }
	            }
	            
	        }
	        
	        Label {
	            id: _help
	            text: "When choosing a ROM, the SD Card will be the default location to search"
	            multiline: true
	            visible: helpEnabled
	            textStyle {
	                base: SystemDefaults.TextStyles.BodyText
	                fontStyle: FontStyle.Italic
	            } 
	        }
	        
	        Divider {}
	        
	        Container {
	            horizontalAlignment: HorizontalAlignment.Center
	            
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }
	        
	            Label {
	                horizontalAlignment: HorizontalAlignment.Left
	                verticalAlignment: VerticalAlignment.Center
	                preferredWidth: 768
	                text: "Per Rom Video Settings"
	            }
	            
	            ToggleButton {
	                id: perRom
	                checked: _frontend.getValueFor(objectName, "true")
	                objectName: "perRom"
	                horizontalAlignment: HorizontalAlignment.Right
	                onCheckedChanged: {
	                    _frontend.saveValueFor(perRom.objectName, checked)
	                }
	            }
	        }
	        
	        Label {
	            id: _help2
	            text: "When a ROM is selected, remember the values previously set for it."
	            multiline: true
	            visible: helpEnabled
	            textStyle {
	                base: SystemDefaults.TextStyles.BodyText
	                fontStyle: FontStyle.Italic
	            } 
	        }
	        
	        Divider {}
	        
	        Container {
	            horizontalAlignment: HorizontalAlignment.Center
	            
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }
	        
	            Label {
	                horizontalAlignment: HorizontalAlignment.Left
	                verticalAlignment: VerticalAlignment.Center
	                preferredWidth: 768
	                text: "Boxart Scraping"
	            }
	            
	            ToggleButton {
	                id: boxart
	                checked: _frontend.getValueFor(objectName, "true")
	                objectName: "boxart"
	                horizontalAlignment: HorizontalAlignment.Right
	                onCheckedChanged: {
	                    _frontend.saveValueFor(boxart.objectName, checked)
	                }
	            }
	        }
	        
	        Label {
	            id: _help3
	            text: "Boxart for roms will be automatically downloaded and displayed."
	            multiline: true
	            visible: helpEnabled
	            textStyle {
	                base: SystemDefaults.TextStyles.BodyText
	                fontStyle: FontStyle.Italic
	            } 
	        }
	        
            Divider {}
            
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                
                Label {
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                    preferredWidth: 768
                    text: "Save History"
                }
                
                ToggleButton {
                    id: saveHistory
                    horizontalAlignment: HorizontalAlignment.Right
                    onCheckedChanged: {
                        _frontend.saveHistory = checked
                    }
                    onCreationCompleted: {
                        checked = _frontend.saveHistory
                    }
                }
            }
            
            Label {
                id: _help4
                text: "Played games will be remembered for easier access."
                multiline: true
                visible: helpEnabled
                textStyle {
                    base: SystemDefaults.TextStyles.BodyText
                    fontStyle: FontStyle.Italic
                } 
            }
            
            Divider {}
            
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                
                Label {
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                    preferredWidth: 768
                    text: "Show FPS"
                }
                
                ToggleButton {
                    id: showFPS
                    horizontalAlignment: HorizontalAlignment.Right
                    onCheckedChanged: {
                        _frontend.showFPS = checked
                    }
                    onCreationCompleted: {
                        checked = _frontend.showFPS
                    }
                }
            }
            
            Label {
                id: _help5
                text: "Show a graph of the emulators frames per second."
                multiline: true
                visible: helpEnabled
                textStyle {
                    base: SystemDefaults.TextStyles.BodyText
                    fontStyle: FontStyle.Italic
                } 
            }
            
            Divider {}
	        
	        Container {
	            visible: !_frontend.isOSThree
    	        Container {
    	            leftPadding: 15.0
    	            Label {
    	                text: qsTr("Default Theme")
    	                leftMargin: 15.0
    	            }
    	        }
    	        DropDown {
    	            horizontalAlignment: HorizontalAlignment.Center
    	            title: qsTr("Visual Theme")
    	            Option {
    	                text: qsTr("Bright")
    	            }
    	            Option {
    	                text: qsTr("Dark")
    	            }
    	            
    	            onSelectedIndexChanged: {
    	                _frontend.setBright(selectedIndex)
    	            }
    	            
    	            onCreationCompleted: {
    	                selectedIndex = _frontend.colorIndex
    	            }
    	        }
    	        Container {
    	            leftPadding: 15.0
    	            rightPadding: 15.0
    	            Label {
    	                text: qsTr("Restart the emulator for the colour theme change to take effect.")
    	                multiline: true
    	            }
    	        }
    	    }
	        Container {
	            visible: _frontend.isOSThree
	            horizontalAlignment: HorizontalAlignment.Fill
	            Button {
	                horizontalAlignment: HorizontalAlignment.Fill
	                text: qsTr("Set Visual Style")
	                
	                onClicked: {
	                    var sheet = themeSheet.createObject()
	                    sheet.open()
	                }
	                
	                attachedObjects: [
	                    ComponentDefinition {
	                        id: themeSheet
	                        source: "theme.qml"
	                    }
	                ]
	            }
	        }
	    }
	}
}