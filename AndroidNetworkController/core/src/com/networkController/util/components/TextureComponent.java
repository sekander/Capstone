package com.networkController.util.components;

import com.badlogic.ashley.core.Component;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class TextureComponent implements Component {

    public TextureRegion region;

    public Texture texture;
    public float width;
    public float height;

}
