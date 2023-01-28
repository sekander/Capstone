package com.networkController.util.screen.transitions.implement;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Interpolation;
import com.networkController.util.Direction;
import com.networkController.util.GdxUtils;
import com.networkController.util.Validate;
import com.networkController.util.screen.transitions.ScreenTransitionBase;

public class SlideScreenTransition extends ScreenTransitionBase {
    private boolean slideIn;
    private Direction direction;
    private Interpolation interpolation;

    public SlideScreenTransition(float duration){
        this(duration, false);
    }

    public SlideScreenTransition(float duration, boolean slideIn){
        this(duration, slideIn, Direction.LEFT);
    }

    public SlideScreenTransition(float duration, boolean slideIn, Direction direction)
    {
        this(duration, slideIn, direction, Interpolation.linear);
    }

    public SlideScreenTransition(float duration, boolean slideIn, Direction direction, Interpolation interpolation) {
        super(duration);

        Validate.notNull(direction, "direction is required");
        Validate.notNull(interpolation, "interpolation is required");

        this.slideIn = slideIn;
        this.direction = direction;
        this.interpolation = interpolation;
    }

    @Override
    public void render(SpriteBatch batch, Texture currentScreen, Texture nextScreen, float percentage) {
        percentage = interpolation.apply(percentage);

        float x = 0.0f;
        float y = 0.0f;

        //drawing order depends on slide type (in or out)
        Texture bottomTexture = slideIn ? currentScreen : nextScreen;
        Texture topTexture = slideIn ? nextScreen : currentScreen;

        int bottomTextureWidth = bottomTexture.getWidth();
        int bottomTextureHeight = bottomTexture.getHeight();
        int topTextureWidth = topTexture.getHeight();
        int topTextureHeight = topTexture.getHeight();

        //calculate position offset
        if(direction.isLeft() || direction.isRight())
        {
            float sign = direction.isLeft() ? -1 : 1;   //sign always -1 or 1
            x = sign * topTextureWidth * percentage;
            if(slideIn) {
                sign = -sign;   //reverse sign
                x += sign * topTextureWidth;
            }
        }

        if(direction.isUp() || direction.isDown())
        {
            float sign = direction.isUp() ? 1 : -1;   //sign always -1 or 1
            y = sign * topTextureHeight * percentage;
            if(slideIn) {
                sign = -sign;   //reverse sign
                y += sign * topTextureHeight;
            }
        }

        //drawing
        GdxUtils.clearScreen();
        batch.begin();

            //bottom texture
            batch.draw(bottomTexture, 0, 0, 0, 0, bottomTextureWidth, bottomTextureHeight,
                    1, 1, 0, 0, 0, bottomTextureWidth, bottomTextureHeight, false, true);

            //top texture
            batch.draw(topTexture, x, y, topTextureWidth / 2.0f, topTextureHeight/2.0f, topTextureWidth, topTextureHeight,
                1, 1, 0, 0, 0, topTextureWidth, topTextureHeight, false, true);

        batch.end();


        /*
        if(direction.isLeft()){
            x = -topTextureWidth * percentage;
            if(slideIn)
                x += topTextureWidth;
        } else if(direction.isRight()){
            x = topTextureWidth * percentage;
            if(slideIn)
                x -= topTextureWidth;
        }
        */

    }
}
