package com.networkController.screen.menu_screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.ImageButton;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.utils.ChangeListener;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.networkController.util.assets.AssetDescriptors;
import com.networkController.screen.game_screen.NetworkTest;
import com.networkController.screen.transition.ScreenTransitions;
import com.networkController.util.GdxUtils;
import com.networkController.util.game.GameBase;
import com.networkController.util.screen.ScreenBaseAdapter;

public class MenuScreen extends ScreenBaseAdapter {
    // == attributes ==
    private final GameBase game;
    private final AssetManager assetManager;

    private Viewport viewport;
    private Stage stage;

    private Texture panel;
    private Texture play_button;
    private Texture play_button_pressed;
    private Texture options_button;
    private Texture options_button_pressed;
    private Texture high_score_button;
    private Texture high_score_button_pressed;
    private Texture quit_button;
    private Texture quit_button_pressed;
    private Texture ui_background;
    private Texture ui_foreground;



    // == constructors ==
    public MenuScreen(GameBase game) {
        this.game = game;
        assetManager = game.getAssetManager();
    }

    // == public methods ==
    @Override
    public void show() {

        viewport = new FitViewport(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        stage = new Stage(viewport, game.getBatch());
        stage.setDebugAll(true);

        Table table = new Table();

        options_button = assetManager.get(AssetDescriptors.UI_OPTIONS_BUTTON);
        options_button_pressed = assetManager.get(AssetDescriptors.UI_OPTIONS_BUTTON_PRESSED);
        panel = assetManager.get(AssetDescriptors.UI_PANEL);
        play_button = assetManager.get(AssetDescriptors.UI_PLAY_BUTTON);
        play_button_pressed = assetManager.get(AssetDescriptors.UI_PLAY_BUTTON_PRESSED);

        high_score_button = assetManager.get(AssetDescriptors.UI_HIGH_SCORE_BUTTON);
        high_score_button_pressed = assetManager.get(AssetDescriptors.UI_HIGH_SCORE_BUTTON_PRESSED);
        quit_button = assetManager.get(AssetDescriptors.UI_QUIT_BUTTON);
        quit_button_pressed = assetManager.get(AssetDescriptors.UI_QUIT_BUTTON_PRESSED);

        ui_background = assetManager.get(AssetDescriptors.UI_BACKGROUND);
        ui_foreground = assetManager.get(AssetDescriptors.UI_FOREGROUND);



        //table.setBackground(new TextureRegionDrawable(background));
        table.setBackground(new TextureRegionDrawable(ui_background));
        table.add(new Image(new Sprite(ui_foreground))).row();

        //buttons
        ImageButton playButton = new ImageButton(createButton(play_button, play_button_pressed));
        ImageButton optionsButton = new ImageButton(createButton(options_button, options_button_pressed));
        ImageButton highScoreButton = new ImageButton(createButton(high_score_button, high_score_button_pressed));
        ImageButton quitButton = new ImageButton(createButton(quit_button, quit_button_pressed));

        playButton.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                play();
            }
        });

        optionsButton.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
//                option();
            }
        });
        quitButton.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
                quit();
            }
        });

        highScoreButton.addListener(new ChangeListener() {
            @Override
            public void changed(ChangeEvent event, Actor actor) {
//                highScore();
            }
        });

        //play table
        Table buttonTable = new Table();
        buttonTable.defaults().pad(20);
        buttonTable.setBackground(new TextureRegionDrawable(panel));
        buttonTable.add(playButton).row();
        buttonTable.add(optionsButton).row();
        buttonTable.add(highScoreButton).row();
        buttonTable.add(quitButton).row();
        buttonTable.center();



        table.add(buttonTable);

        table.center();
        table.setFillParent(true);
        table.pack();




        stage.addActor(table);

        Gdx.input.setInputProcessor(stage);
    }

    @Override
    public void render(float delta) {
        GdxUtils.clearScreen();
        stage.act();
        stage.draw();
    }

    @Override
    public void resize(int width, int height) {
        viewport.update(width, height, true);
    }

    @Override
    public void hide() {
        dispose();
    }

    @Override
    public void dispose() {
        Gdx.input.setInputProcessor(null);
        stage.dispose();
    }

    @Override
    public InputProcessor getInputProccessor() {
        return stage;
    }

    // == private methods ==
    private void play() {
        //game.setScreen(new GameScrenn(game));
        //game.setScreen(new Box2DScreen(game), ScreenTransitions.FADE);
        game.setScreen(new NetworkTest(game), ScreenTransitions.SCALE);
        //game.setScreen(new Box2DScreen(game), ScreenTransitions.SLIDE);
    }

    private void quit() {
        Gdx.app.exit();
    }
}
