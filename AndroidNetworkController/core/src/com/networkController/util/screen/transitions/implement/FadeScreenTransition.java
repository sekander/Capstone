package com.networkController.util.screen.transitions.implement;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Interpolation;
import com.networkController.util.GdxUtils;
import com.networkController.util.screen.transitions.ScreenTransitionBase;

public class FadeScreenTransition extends ScreenTransitionBase {
    public FadeScreenTransition(float duration) {
        super(duration);
    }

    @Override
    public void render(SpriteBatch batch, Texture currentScreen, Texture nextScreen, float percentage) {
        int currentScreenWidth = currentScreen.getWidth();
        int currentScreenHeight = currentScreen.getHeight();
        int nextScreenWidth = nextScreen.getWidth();
        int nextScreenHeight = nextScreen.getHeight();

        //interpolate percentage
        percentage = Interpolation.fade.apply(percentage);

        //clear screen
        GdxUtils.clearScreen();

        batch.begin();
            //draw current screen
            Color oldColor = batch.getColor().cpy();
            batch.setColor(1, 1, 1, 1.0f - percentage);
            batch.draw(currentScreen, 0, 0, 0, 0, currentScreenWidth, currentScreenHeight,
                                        1, 1, 0, 0, 0, currentScreenWidth, currentScreenHeight,
                                        false, true);

            //draw next screen
            batch.setColor(1, 1, 1, percentage);    //white colour transparency
            batch.draw(nextScreen, 0, 0, 0, 0, nextScreenWidth, nextScreenHeight,
                                      1, 1, 0, 0, 0, nextScreenWidth, nextScreenHeight,
                                        false, true);
            //set old colour back
            batch.setColor(oldColor);

        batch.end();
    }
}
