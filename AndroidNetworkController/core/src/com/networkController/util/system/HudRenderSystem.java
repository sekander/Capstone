package com.networkController.util.system;

import com.badlogic.ashley.core.EntitySystem;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.GlyphLayout;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.viewport.Viewport;

public class HudRenderSystem extends EntitySystem {
    private final Viewport viewport;
    private final SpriteBatch batch;
    private BitmapFont font;

   private final GlyphLayout layout = new GlyphLayout();

    public HudRenderSystem(Viewport viewport, SpriteBatch batch, BitmapFont font) {
        this.viewport = viewport;
        this.batch = batch;
        this.font = font;
    }

    @Override
    public void update(float deltaTime) {
       viewport.apply();
       batch.setProjectionMatrix(viewport.getCamera().combined);
       batch.begin();

        draw();

       batch.end();
    }

    private void draw(){
        /*
        String life = "LIVES: " + GameManager.INSTANCE.getLives();
        layout.setText(font, life);
        font.draw(batch, life, 20, GameConfig.HUD_HEIGHT - layout.height);

        String score = "SCORE: " + GameManager.INSTANCE.getScore();
        layout.setText(font, score);
        font.draw(batch, score, GameConfig.HUD_WIDTH - layout.width - 20,
                GameConfig.HUD_HEIGHT - layout.height);
        */
    }
}
