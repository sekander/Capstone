package com.networkController.screen.loading_screen;

import com.badlogic.gdx.assets.AssetDescriptor;
import com.badlogic.gdx.utils.Array;
import com.networkController.screen.game_screen.NetworkTest;
import com.networkController.screen.menu_screen.MenuScreen;
import com.networkController.screen.transition.ScreenTransitions;
import com.networkController.util.assets.AssetDescriptors;
import com.networkController.util.game.GameBase;
import com.networkController.util.screen.loading.LoadingScreenBase;

public class LoadingScreen extends LoadingScreenBase {
    public LoadingScreen(GameBase game) {
        super(game);
    }

    /* access modifiers changed from: protected */
    public Array<AssetDescriptor> getAssetDescriptors() {
        return AssetDescriptors.ALL;
    }

    /* access modifiers changed from: protected */
    public void onLoadDone() {
        this.game.setScreen(new MenuScreen(this.game), ScreenTransitions.FADE);
        //this.game.setScreen(new NetworkTest(this.game, "192.168.2.18"), ScreenTransitions.FADE);
    }
}
