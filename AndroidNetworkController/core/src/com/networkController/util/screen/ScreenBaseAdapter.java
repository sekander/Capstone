package com.networkController.util.screen;

import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.ui.ImageButton;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;

public abstract class ScreenBaseAdapter implements ScreenBase{
    @Override
    public InputProcessor getInputProccessor() {
        return null;
    }

    @Override
    public void show() {

    }

    @Override
    public void render(float delta) {

    }

    @Override
    public void resize(int width, int height) {

    }

    @Override
    public void pause() {

    }

    @Override
    public void resume() {

    }

    @Override
    public void hide() {

    }

    @Override
    public void dispose() {

    }

    protected ImageButton.ImageButtonStyle createButton(Texture button, Texture buttonPressed){

        ImageButton.ImageButtonStyle style = new ImageButton.ImageButtonStyle();
        style.imageUp = new TextureRegionDrawable(new TextureRegion(button));
        style.checked = style.imageUp;
        style.imageDown = new TextureRegionDrawable(new TextureRegion(buttonPressed));

        return style;
    }
}
