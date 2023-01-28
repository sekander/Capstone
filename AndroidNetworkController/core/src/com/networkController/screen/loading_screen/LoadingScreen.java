package com.networkController.screen.loading_screen;

import com.badlogic.gdx.assets.AssetDescriptor;
import com.badlogic.gdx.utils.Array;
import com.networkController.screen.game_screen.NetworkTest;
import com.networkController.screen.transition.ScreenTransitions;
import com.networkController.util.game.GameBase;
import com.networkController.util.screen.loading.LoadingScreenBase;
import com.networkController.util.assets.AssetDescriptors;

public class LoadingScreen extends LoadingScreenBase {
    // == constructors ==
    public LoadingScreen(GameBase game) {
        super(game);
    }

    // == protected methods ==
    @Override
    protected Array<AssetDescriptor> getAssetDescriptors() {
        return AssetDescriptors.ALL;
    }


    @Override
    protected void onLoadDone() {
        game.setScreen(new NetworkTest(game), ScreenTransitions.FADE);
    }


}
