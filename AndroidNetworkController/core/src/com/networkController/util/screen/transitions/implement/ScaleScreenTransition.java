package com.networkController.util.screen.transitions.implement;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Interpolation;
import com.networkController.util.GdxUtils;
import com.networkController.util.Validate;
import com.networkController.util.screen.transitions.ScreenTransitionBase;

public class ScaleScreenTransition extends ScreenTransitionBase {

    private boolean scaleOut;
    private Interpolation interpolation;

    public ScaleScreenTransition(float duration){
        this(duration, false);
    }

    public ScaleScreenTransition(float duration, boolean scaleOut)
    {
        this(duration, scaleOut, Interpolation.linear);
    }

    public ScaleScreenTransition(float duration, boolean scaleOut, Interpolation interpolation) {
        super(duration);

        Validate.notNull(interpolation, "interplolation is required");
        this.scaleOut = scaleOut;
        this.interpolation = interpolation;
    }

    @Override
    public void render(SpriteBatch batch, Texture currentScreen, Texture nextScreen, float percentage) {
        //interpolate percentage
        percentage = interpolation.apply(percentage);

        //assume scale out is false
        float scale = 1-percentage;

        if(scaleOut)
            scale = percentage;

        //drawing order depends on scale type (in or out)
        Texture topTexture = scaleOut ? nextScreen : currentScreen;
        Texture bottomTexture = scaleOut ? currentScreen : nextScreen;

        int topTextureWidth = topTexture.getWidth();
        int topTextureHeight = topTexture.getHeight();
        int bottomTextureWidth = bottomTexture.getWidth();
        int bottomTextureHeight = bottomTexture.getHeight();

        //drawing
        GdxUtils.clearScreen();
        batch.begin();

            //bottom texture
            batch.draw(bottomTexture, 0, 0, 0, 0, bottomTextureWidth, bottomTextureHeight,
                    1, 1, 0, 0, 0, bottomTextureWidth, bottomTextureHeight, false, true);

            //top texture
            batch.draw(topTexture, 0, 0, topTextureWidth / 2.0f, topTextureHeight/2.0f, topTextureWidth, topTextureHeight,
                scale, scale, 0, 0, 0, topTextureWidth, topTextureHeight, false, true);

        batch.end();

    }
}
