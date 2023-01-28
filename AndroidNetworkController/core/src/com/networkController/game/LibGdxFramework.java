package com.networkController.game;

import com.networkController.screen.loading_screen.LoadingScreen;
import com.networkController.util.game.GameBase;

public class LibGdxFramework extends GameBase {

    public LibGdxFramework(){super();}

    @Override
    public void postCreate() {
        setScreen(new LoadingScreen(this));
    }
}
