package com.networkController.util.assets;

import com.badlogic.gdx.assets.AssetDescriptor;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.utils.Array;

public class AssetDescriptors {

    public static final AssetDescriptor<BitmapFont> FONT =
            new AssetDescriptor<BitmapFont>("ui/fonts/ui_font_32.fnt", BitmapFont.class);

    public static final AssetDescriptor<Sound> HIT_SOUND =
            new AssetDescriptor<Sound>("sounds/Point.wav", Sound.class);

    public static final AssetDescriptor<Texture> BACK_BACKGROUND =
            new AssetDescriptor<Texture>("background/Clouds_1/1.png", Texture.class);


    public static final AssetDescriptor<Texture> FRONT_BACKGROUND =
            new AssetDescriptor<Texture>("background/black_stars.png", Texture.class);

    public static final AssetDescriptor<Texture> BACKGROUND =
            new AssetDescriptor<Texture>("gameplay/background.png", Texture.class);
    public static final AssetDescriptor<Texture> OBSTACLE =
            new AssetDescriptor<Texture>("gameplay/obstacle.png", Texture.class);
    public static final AssetDescriptor<Texture> PLAYER =
            new AssetDescriptor<Texture>("gameplay/player.png", Texture.class);

    public static final AssetDescriptor<Texture> UI_BACK_BUTTON =
            new AssetDescriptor<Texture>("ui/back.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_BACK_BUTTON_PRESSED =
            new AssetDescriptor<Texture>("ui/backPressed.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_CHECK_MARK =
            new AssetDescriptor<Texture>("ui/check-mark.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_EASY_BUTTON =
            new AssetDescriptor<Texture>("ui/easy.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_HARD_BUTTON =
            new AssetDescriptor<Texture>("ui/hard.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_HIGH_SCORE_BUTTON =
            new AssetDescriptor<Texture>("ui/Buttons/BTNs/Rating_BTN.png", Texture.class);
            //new AssetDescriptor<Texture>("ui/highScore.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_HIGH_SCORE_BUTTON_PRESSED =
            new AssetDescriptor<Texture>("ui/Buttons/BTNs_Active/Rating_BTN.png", Texture.class);
            //new AssetDescriptor<Texture>("ui/highScorePressed.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_MEDIUM_BUTTON =
            new AssetDescriptor<Texture>("ui/medium.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_OPTIONS_BUTTON =
            new AssetDescriptor<Texture>("ui/options.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_OPTIONS_BUTTON_PRESSED =
            new AssetDescriptor<Texture>("ui/optionsPressed.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_PANEL =
            new AssetDescriptor<Texture>("ui/panel.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_PLAY_BUTTON =
            new AssetDescriptor<Texture>("ui/play.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_PLAY_BUTTON_PRESSED =
            new AssetDescriptor<Texture>("ui/playPressed.png", Texture.class);

    public static final AssetDescriptor<Texture> UI_QUIT_BUTTON =
            new AssetDescriptor<Texture>("ui/Buttons/BTNs/Close_BTN.png", Texture.class);
    public static final AssetDescriptor<Texture> UI_QUIT_BUTTON_PRESSED =
            new AssetDescriptor<Texture>("ui/Buttons/BTNs_Active/Close_BTN.png", Texture.class);

//    back.png  backPressed.png  check-mark.png  easy.png  hard.png  highscore.png  highscorePressed.png  medium.png
//    options.png  optionsPressed.png  panel.png  play.png  playPressed.png

    public static final AssetDescriptor<Texture> UI_BACKGROUND =
            new AssetDescriptor<Texture>("background/Clouds_1/1.png", Texture.class);

    public static final AssetDescriptor<Texture> UI_FOREGROUND =
            new AssetDescriptor<Texture>("background/Clouds_1/2.png", Texture.class);


    // all descriptors
    public static final Array<AssetDescriptor> ALL = new Array<AssetDescriptor>(
    );

    static {
        ALL.addAll(
                FONT,
                BACKGROUND,
                OBSTACLE,
                PLAYER,
                UI_BACKGROUND,
                UI_FOREGROUND,
                UI_BACK_BUTTON,
                UI_CHECK_MARK,
                UI_EASY_BUTTON,
                UI_BACK_BUTTON_PRESSED,
                UI_HARD_BUTTON,
                UI_HIGH_SCORE_BUTTON,
                UI_HIGH_SCORE_BUTTON_PRESSED,
                UI_BACKGROUND,
                UI_FOREGROUND,
                UI_MEDIUM_BUTTON,
                UI_OPTIONS_BUTTON,
                UI_OPTIONS_BUTTON_PRESSED,
                UI_PANEL,
                UI_PLAY_BUTTON,
                UI_PLAY_BUTTON_PRESSED,
                UI_QUIT_BUTTON,
                UI_QUIT_BUTTON_PRESSED
        );
    }
    private AssetDescriptors() {
    }
}
