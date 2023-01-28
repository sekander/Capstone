package com.networkController.util.controller;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.controllers.Controller;
import com.badlogic.gdx.controllers.ControllerAdapter;
import com.badlogic.gdx.controllers.ControllerListener;
import com.badlogic.gdx.controllers.Controllers;
import com.badlogic.gdx.utils.Array;

public class GamePAD {
    private Controller markedCurrentController;
    private ControllerListener controllerListener;

    private int callbackCount;


    public GamePAD() {

        controllerListener = new ControllerAdapter() {
            @Override
            public void connected(final Controller controller) {
                Gdx.app.log("CONTROLLER Adapter: ", "Controller connected: " + controller.getName()
                        + "/" + controller.getUniqueId());
            }

            @Override
            public void disconnected(Controller controller) {
                Gdx.app.log("Controller Adapter: ", "Controller disconnected: " + controller.getName()
                        + "/" + controller.getUniqueId());
            }
        };

        refreshControllersList();
    }

    private void refreshControllersList() {
        Array<String> controllerNames = new Array<>();
        markedCurrentController = Controllers.getCurrent();
        int markedIndex = 0;
        controllerNames.add("Select...");
        Gdx.app.log("CONTROLLERS:", Controllers.getControllers().size + " controllers connected.");
        for (int i = 0; i < Controllers.getControllers().size; i++) {
            Controller controller = Controllers.getControllers().get(i);
            String name = controller.getName();
            Gdx.app.log("Controllers", name + "/" + controller.getUniqueId());

            if (controller == markedCurrentController) {
                name = "-> " + name;
                markedIndex = controllerNames.size;
            }

            if (name.length() > 30)
                name = name.substring(0, 28) + "...";
            controllerNames.add(name);
            controller.addListener(controllerListener);
            markedCurrentController = controller;
        }
    }
    public boolean gamePadLeft(){
        if(markedCurrentController == null)
            return false;

        if(markedCurrentController.isConnected()) {
            if (markedCurrentController.getButton(markedCurrentController.getMapping().buttonDpadLeft)) {
                Gdx.app.log("CONTROLLER: ", "LEFT Pressed");
            }
            return true;
        }

        return false;
    }

    public boolean gamePadRight(){
        if(markedCurrentController == null)
            return false;

        if(markedCurrentController.isConnected()) {
            if (markedCurrentController.getButton(markedCurrentController.getMapping().buttonDpadRight)) {
                Gdx.app.log("CONTROLLER: ", "RIGHT Pressed");
                return true;
            }
        }

        return false;
    }

    public Controller getMarkedCurrentController() {
        return markedCurrentController;
    }

    public void update(){
        if(markedCurrentController == null)
            return;


        if(markedCurrentController.isConnected()) {
            if (markedCurrentController.getButton(markedCurrentController.getMapping().buttonA))
                Gdx.app.log("CONTROLLER: ", "A Pressed");
        }

        gamePadLeft();
        gamePadRight();
    }
}
