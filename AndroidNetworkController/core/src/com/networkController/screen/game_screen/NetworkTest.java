package com.networkController.screen.game_screen;

import com.badlogic.ashley.core.PooledEngine;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.GlyphLayout;
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Dialog;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.utils.Json;
import com.badlogic.gdx.utils.JsonReader;
import com.badlogic.gdx.utils.JsonValue;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.networkController.util.assets.AssetDescriptors;
import com.networkController.util.common.EntityFactory;
import com.networkController.util.controller.AndroidController;
import com.networkController.util.controller.GamePAD;
import com.networkController.util.game.GameBase;
import com.networkController.util.physics.BodyFactory;
import com.networkController.util.screen.ScreenBaseAdapter;
import com.networkController.util.system.HudRenderSystem;
import com.networkController.util.system.RenderSystem;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class NetworkTest extends ScreenBaseAdapter {
    DatagramSocket aSocket = null;
    private final AssetManager assetManager;
    float axisLX;
    float axisLY;
    float axisRX;
    float axisRY;
    private OrthographicCamera camera;
    boolean connected = false;
    String connectedSubnet;
    AndroidController controller;
    private ShapeRenderer debugRender;
    Dialog dialog;
    private PooledEngine engine;
    private EntityFactory factory;
    BitmapFont font;
    private final GameBase game;
    GamePAD gamePAD;
    Json json;
    JsonReader jsonR;
    String jsonString;
    GlyphLayout layout;
    String leftStick;
    BitmapFont menuLabel;
    Json pjson;
    private String playerAddrenaline;
    private String playerAntkti;
    private String playerArmor;
    private String playerEmgkti;
    private String playerFortify;
    private String playerHealth;
    private String playerLocation;
    private String playerMedkit;
    private String playerRepairKits;
    private String playerTraps;
    /* access modifiers changed from: private */
    public String response;
    String rightStick;
    String serverData;
    private boolean show_inventory;
    private boolean show_stats;
    private Skin skin;
    BitmapFont smfont;
    private Stage stage;
    boolean testConnection = false;
    private boolean touchPad_10_touched;
    private boolean touchPad_11_touched;
    private boolean touchPad_12_touched;
    private boolean touchPad_13_touched;
    private boolean touchPad_1_touched;
    private boolean touchPad_2_touched;
    private boolean touchPad_3_touched;
    private boolean touchPad_4_touched;
    private boolean touchPad_5_touched;
    private boolean touchPad_6_touched;
    private boolean touchPad_7_touched;
    private boolean touchPad_8_touched;
    private boolean touchPad_9_touched;
    int touchpad_3_counter;
    String value;
    private Viewport viewport;
    double gameClock;
    double capturedTime;

    public NetworkTest(GameBase game2, String subnet) {
        this.game = game2;
        this.assetManager = game2.getAssetManager();
        this.connectedSubnet = subnet;
    }

    private void initialize() {
        this.layout = new GlyphLayout();
        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ui/fonts/Minecraft.ttf"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 10;
        BitmapFont bitmapFont = (BitmapFont) this.assetManager.get(AssetDescriptors.FONT);
        this.font = bitmapFont;
        bitmapFont.getData().setScale(0.5f, 0.5f);
        BitmapFont generateFont = generator.generateFont(parameter);
        this.font = generateFont;
        generateFont.setColor(Color.GREEN);
        FreeTypeFontGenerator smgenerator = new FreeTypeFontGenerator(Gdx.files.internal("ui/fonts/Sans.ttf"));
        FreeTypeFontGenerator.FreeTypeFontParameter smParameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        smParameter.size = 20;
        BitmapFont bitmapFont2 = (BitmapFont) this.assetManager.get(AssetDescriptors.FONT);
        this.smfont = bitmapFont2;
        bitmapFont2.getData().setScale(0.25f, 0.25f);
        BitmapFont generateFont2 = smgenerator.generateFont(smParameter);
        this.smfont = generateFont2;
        generateFont2.setColor(Color.RED);
        FreeTypeFontGenerator menuLabelGenerator = new FreeTypeFontGenerator(Gdx.files.internal("ui/fonts/Sans.ttf"));
        FreeTypeFontGenerator.FreeTypeFontParameter menuParamenter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        menuParamenter.size = 10;
        BitmapFont bitmapFont3 = (BitmapFont) this.assetManager.get(AssetDescriptors.FONT);
        this.menuLabel = bitmapFont3;
        bitmapFont3.getData().setScale(0.25f, 0.25f);
        BitmapFont generateFont3 = menuLabelGenerator.generateFont(menuParamenter);
        this.menuLabel = generateFont3;
        generateFont3.setColor(Color.RED);
        PooledEngine pooledEngine = new PooledEngine();
        this.engine = pooledEngine;
        pooledEngine.addSystem(new RenderSystem(this.viewport, this.game.getBatch()));
        this.engine.addSystem(new HudRenderSystem(this.viewport, this.game.getBatch(), this.font));
        this.factory = new EntityFactory(this.engine, this.assetManager, (BodyFactory) null);
        this.gamePAD = new GamePAD();
        this.controller = new AndroidController();
        this.jsonR = new JsonReader();
        this.json = new Json();
        this.jsonString = "";
        this.rightStick = "Right Trigger \nx: " + this.axisRX + ", y: " + this.axisRY + "\nRight Joystick \n" + this.rightStick;
        this.leftStick = "\n\nLeft Trigger \nx: " + this.axisLX + ", y: " + this.axisLY + "\nLeft Joystick \n" + this.leftStick;
        this.pjson = new Json();
        this.show_inventory = true;
        this.show_stats = false;
        this.touchpad_3_counter = 0;
        this.touchPad_1_touched = false;
        this.touchPad_2_touched = false;
        this.touchPad_3_touched = false;
        this.touchPad_4_touched = false;
        this.touchPad_5_touched = false;
        this.touchPad_6_touched = false;
        this.touchPad_7_touched = false;
        this.touchPad_8_touched = false;
        this.touchPad_9_touched = false;
        this.touchPad_10_touched = false;
        this.touchPad_11_touched = false;
        this.touchPad_12_touched = false;
        this.touchPad_13_touched = false;
    }

    private void networkInit() {
        new Thread(new Runnable() {
            public void run() {
                String subnet = NetworkTest.this.connectedSubnet;
                //String subnet = "192.168.2.18";

                Gdx.app.log("AndroidNetwork", subnet);
                NetworkTest.this.connected = true;
                while (true) {
                    try {
                        NetworkTest.this.aSocket = new DatagramSocket();
                        NetworkTest.this.aSocket.setSoTimeout(5000);
                        byte[] buffer = new byte[1024];
                        NetworkTest.this.aSocket.connect(InetAddress.getByName(subnet), 2222);
                        try {
                            Thread.sleep(50);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        byte[] n = NetworkTest.this.jsonString.getBytes();
                        NetworkTest.this.aSocket.send(new DatagramPacket(n, n.length));
                        DatagramPacket receivePacket = new DatagramPacket(buffer, buffer.length);
                        NetworkTest.this.aSocket.receive(receivePacket);
                        String unused = NetworkTest.this.response = NetworkTest.removeNonAlphanumeric(new String(receivePacket.getData()));
                        if (NetworkTest.this.aSocket == null) {
                        }
                    } catch (SocketException e2) {
                        System.out.println("Socket: " + e2.getMessage());
                        if (NetworkTest.this.aSocket == null) {
                        }
                    } catch (IOException e3) {
                        System.out.println("IO: " + e3.getMessage());
                        if (NetworkTest.this.aSocket == null) {
                        }
                    } catch (Throwable th) {
                        if (NetworkTest.this.aSocket != null) {
                            NetworkTest.this.aSocket.close();
                        }
                        throw th;
                    }
                    NetworkTest.this.aSocket.close();
                }
            }
        }).start();
    }

    public void show() {
        this.camera = new OrthographicCamera();
        this.viewport = new FitViewport((float) (Gdx.graphics.getWidth() / 10), (float) (Gdx.graphics.getHeight() / 10), this.camera);
        this.debugRender = new ShapeRenderer();
        this.stage = new Stage(this.viewport, this.game.getBatch());
        Gdx.input.setInputProcessor(this.stage);
        this.stage.setDebugAll(true);
        initialize();
        networkInit();
    }

    public static String removeNonAlphanumeric(String str) {
        return str.replaceAll("[^a-zA-Z0-9{}:.,\"]", "");
    }

    private void controllerUpdate() {
        /*
        this.controller.setTouchX(String.valueOf(Gdx.input.getX()));
        this.controller.setTouchY(String.valueOf(Gdx.input.getY()));
        if (Gdx.input.isPeripheralAvailable(Input.Peripheral.Gyroscope)) {
            this.controller.setGyroX(String.valueOf(Gdx.input.getGyroscopeX()));
            this.controller.setGyroY(String.valueOf(Gdx.input.getGyroscopeY()));
            this.controller.setGyroZ(String.valueOf(Gdx.input.getGyroscopeZ()));
        }
        */
        if (this.touchPad_1_touched) {
            this.controller.setTouchPad_1("1");
        } else {
            this.controller.setTouchPad_1("0");
        }
        if (this.touchPad_2_touched) {
            this.controller.setTouchPad_2("1");
        } else {
            this.controller.setTouchPad_2("0");
        }
        if (this.touchPad_3_touched) {
            this.controller.setTouchPad_3("1");
        } else {
            this.controller.setTouchPad_3("0");
        }
        if (this.touchPad_4_touched) {
            this.controller.setTouchPad_4("1");
        } else {
            this.controller.setTouchPad_4("0");
        }
        if (this.touchPad_5_touched) {
            this.controller.setTouchPad_5("1");
        } else {
            this.controller.setTouchPad_5("0");
        }
        if (this.touchPad_6_touched) {
            this.controller.setTouchPad_6("1");
        } else {
            this.controller.setTouchPad_6("0");
        }
        if (this.touchPad_7_touched) {
            this.controller.setTouchPad_7("1");
        } else {
            this.controller.setTouchPad_7("0");
        }
        if (this.touchPad_8_touched) {
            this.controller.setTouchPad_8("1");
        } else {
            this.controller.setTouchPad_8("0");
        }
        if (this.touchPad_9_touched) {
            this.controller.setTouchPad_9("1");
        } else {
            this.controller.setTouchPad_9("0");
        }
        if (this.touchPad_10_touched) {
            this.controller.setTouchPad_10("1");
        } else {
            this.controller.setTouchPad_10("0");
        }
        if (this.touchPad_11_touched) {
            this.controller.setTouchPad_11("1");
        } else {
            this.controller.setTouchPad_11("0");
        }
        if (this.touchPad_12_touched) {
            this.controller.setTouchPad_12("1");
        } else {
            this.controller.setTouchPad_12("0");
        }
        if (this.touchPad_13_touched) {
            this.controller.setTouchPad_13("1");
        } else {
            this.controller.setTouchPad_13("0");
        }

        if (this.gamePAD.getMarkedCurrentController() != null && this.gamePAD.getMarkedCurrentController().isConnected()) {
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonDpadUp)) {
                this.controller.setDpadU("1");
            } else {
                this.controller.setDpadU("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonDpadDown)) {
                this.controller.setDpadD("1");
            } else {
                this.controller.setDpadD("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonDpadRight)) {
                this.controller.setDpadR("1");
            } else {
                this.controller.setDpadR("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonDpadLeft)) {
                this.controller.setDpadL("1");
            } else {
                this.controller.setDpadL("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonA)) {
                this.controller.setA("1");
            } else {
                this.controller.setA("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonB)) {
                this.controller.setB("1");
            } else {
                this.controller.setB("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonX)) {
                this.controller.setX("1");
            } else {
                this.controller.setX("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonY)) {
                this.controller.setY("1");
            } else {
                this.controller.setY("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonL1)) {
                this.controller.setL("1");
            } else {
                this.controller.setL("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonR1)) {
                this.controller.setR("1");
            } else {
                this.controller.setR("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonStart)) {
                this.controller.setSTART("1");
            } else {
                this.controller.setSTART("0");
            }
            if (this.gamePAD.getMarkedCurrentController().getButton(this.gamePAD.getMarkedCurrentController().getMapping().buttonBack)) {
                this.controller.setSELECT("1");
            } else {
                this.controller.setSELECT("0");
            }
            this.controller.setR2(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(2)));
            this.controller.setL2(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(0)));
            this.controller.setRJOYX(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(4)));
            this.controller.setRJOYY(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(6)));
            this.controller.setLJOYX(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(7)));
            this.controller.setLJOYY(String.valueOf(this.gamePAD.getMarkedCurrentController().getAxis(5)));
        }
    }

    private void jsonUpdate() {
        String json2 = this.json.toJson(this.controller);
        this.jsonString = json2;
        String replace = json2.replaceAll("[^\\{\\},]+", "\"$0\"").replace("\"[\"{", "[{").replace(":", "\":\"").replace(" ", "").replace("}\"]\"", "}]").replace("\"true\"", "true").replace("\"false\"", "false");
        this.value = replace;
        this.jsonString = replace;
    }

    private void debugDraw() {
        this.game.getBatch().enableBlending();
        float touchX = (float) Gdx.input.getX();
        float touchY = (float) Gdx.input.getY();
        Gdx.app.log("AndroidTouch", "Touch Pos : " + touchX + ", " + touchY);
        if (Gdx.input.isTouched()) {
            if (touchX > 1900.0f && touchX < 2300.0f && touchY > 50.0f && touchY < 245.0f) {
                DrawDebugSquare(new Vector2(185.0f, 75.0f), new Vector2(45.0f, 25.0f), Color.WHITE, this.camera.combined);
                this.touchPad_1_touched = true;
            }
            if (touchX > 1900.0f && touchX < 2300.0f && touchY > 320.0f && touchY < 500.0f) {
                DrawDebugSquare(new Vector2(185.0f, 50.0f), new Vector2(45.0f, 25.0f), Color.WHITE, this.camera.combined);
                this.touchPad_2_touched = true;
            }
            if (touchX > 1900.0f && touchX < 2300.0f && touchY > 550.0f && touchY < 750.0f) {
                DrawDebugSquare(new Vector2(185.0f, 25.0f), new Vector2(45.0f, 25.0f), Color.WHITE, this.camera.combined);
                this.touchPad_3_touched = true;
            }
            if (touchX > 1900.0f && touchX < 2300.0f && touchY > 800.0f && touchY < 1020.0f) {
                DrawDebugSquare(new Vector2(185.0f, 0.0f), new Vector2(45.0f, 25.0f), Color.WHITE, this.camera.combined);
                this.touchPad_4_touched = true;
            }
            if (touchX > 505.0f && touchX < 935.0f && touchY > 270.0f && touchY < 505.0f) {
                DrawDebugSquare(new Vector2(50.0f, 50.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_5_touched = true;
            }
            if (touchX > 505.0f && touchX < 935.0f && touchY > 522.0f && touchY < 750.0f) {
                DrawDebugSquare(new Vector2(50.0f, 25.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_6_touched = true;
            }
            if (touchX > 505.0f && touchX < 935.0f && touchY > 775.0f && touchY < 1005.0f) {
                DrawDebugSquare(new Vector2(50.0f, 0.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_7_touched = true;
            }
            if (touchX > 960.0f && touchX < 1385.0f && touchY > 270.0f && touchY < 505.0f) {
                DrawDebugSquare(new Vector2(95.0f, 50.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_8_touched = true;
            }
            if (touchX > 960.0f && touchX < 1385.0f && touchY > 522.0f && touchY < 750.0f) {
                DrawDebugSquare(new Vector2(95.0f, 25.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_9_touched = true;
            }
            if (touchX > 960.0f && touchX < 1385.0f && touchY > 775.0f && touchY < 1005.0f) {
                DrawDebugSquare(new Vector2(95.0f, 0.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_10_touched = true;
            }
            if (touchX > 1400.0f && touchX < 1835.0f && touchY > 270.0f && touchY < 505.0f) {
                DrawDebugSquare(new Vector2(140.0f, 50.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_11_touched = true;
            }
            if (touchX > 1400.0f && touchX < 1835.0f && touchY > 522.0f && touchY < 750.0f) {
                DrawDebugSquare(new Vector2(140.0f, 25.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_12_touched = true;
            }
            if (touchX > 1400.0f && touchX < 1835.0f && touchY > 775.0f && touchY < 1005.0f) {
                DrawDebugSquare(new Vector2(140.0f, 0.0f), new Vector2(45.0f, 25.0f), Color.GREEN, this.camera.combined);
                this.touchPad_13_touched = true;
            }
        } else {
            if (this.touchPad_1_touched) {
                this.touchPad_1_touched = false;
            }
            if (this.touchPad_2_touched) {
                this.touchPad_2_touched = false;
            }
            if (this.touchPad_3_touched) {
                this.touchPad_3_touched = false;
            }
            if (this.touchPad_4_touched) {
                this.touchPad_4_touched = false;
            }
            if (this.touchPad_5_touched) {
                this.touchPad_5_touched = false;
            }
            if (this.touchPad_6_touched) {
                this.touchPad_6_touched = false;
            }
            if (this.touchPad_7_touched) {
                this.touchPad_7_touched = false;
            }
            if (this.touchPad_8_touched) {
                this.touchPad_8_touched = false;
            }
            if (this.touchPad_9_touched) {
                this.touchPad_9_touched = false;
            }
            if (this.touchPad_10_touched) {
                this.touchPad_10_touched = false;
            }
            if (this.touchPad_11_touched) {
                this.touchPad_11_touched = false;
            }
            if (this.touchPad_12_touched) {
                this.touchPad_12_touched = false;
            }
            if (this.touchPad_13_touched) {
                this.touchPad_13_touched = false;
            }
        }
        DrawDebugLine(new Vector2(0.0f, 225.0f), new Vector2(0.0f, 0.0f), 2, Color.GREEN, this.camera.combined);
        DrawDebugLine(new Vector2(0.0f, 100.0f), new Vector2(1108.0f, 100.0f), 2, Color.BLUE, this.camera.combined);
        DrawDebugLine(new Vector2(50.0f, 75.0f), new Vector2(230.0f, 75.0f), 2, Color.YELLOW, this.camera.combined);
        if (this.show_inventory) {
            DrawDebugLine(new Vector2(50.0f, 50.0f), new Vector2(230.0f, 50.0f), 2, Color.YELLOW, this.camera.combined);
            DrawDebugLine(new Vector2(50.0f, 25.0f), new Vector2(230.0f, 25.0f), 2, Color.YELLOW, this.camera.combined);
            DrawDebugLine(new Vector2(95.0f, 75.0f), new Vector2(95.0f, 0.0f), 2, Color.ORANGE, this.camera.combined);
            DrawDebugLine(new Vector2(140.0f, 75.0f), new Vector2(140.0f, 0.0f), 2, Color.ORANGE, this.camera.combined);
        }
        DrawDebugLine(new Vector2(185.0f, 100.0f), new Vector2(185.0f, 0.0f), 2, Color.GREEN, this.camera.combined);
        DrawDebugLine(new Vector2(50.0f, 0.0f), new Vector2(50.0f, 100.0f), 2, Color.GREEN, this.camera.combined);
        DrawDebugLine(new Vector2(0.0f, 33.0f), new Vector2(50.0f, 33.0f), 2, Color.RED, this.camera.combined);
        DrawDebugLine(new Vector2(0.0f, 66.0f), new Vector2(50.0f, 66.0f), 2, Color.RED, this.camera.combined);
        DrawDebugLine(new Vector2(0.0f, 0.0f), new Vector2(1108.0f, 0.0f), 2, Color.BLUE, this.camera.combined);
        DrawDebugLine(new Vector2(230.0f, 225.0f), new Vector2(230.0f, 0.0f), 2, Color.GREEN, this.camera.combined);
        this.game.getBatch().begin();
        if (!(this.response == null && this.serverData == null)) {
            this.font.getData().setScale(0.9f);
            if (this.response.contains("xpos")) {
                JsonValue fromJson = new JsonReader().parse(this.response);
                this.playerLocation = fromJson.getString("xpos") + "\n" + fromJson.getString("ypos");
                this.playerHealth = fromJson.getString("health");
                this.playerMedkit = fromJson.getString("med");
                this.playerEmgkti = fromJson.getString("emg");
                this.playerAntkti = fromJson.getString("ant");
                this.playerArmor = fromJson.getString("arm");
                this.playerAddrenaline = fromJson.getString("add");
                this.playerTraps = fromJson.getString("trp");
                this.playerRepairKits = fromJson.getString("rep");
                this.playerFortify = fromJson.getString("frt");
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "HEALTH: \n" + this.playerHealth, 5.0f, 95.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "ARMOUR: \n" + this.playerArmor, 5.0f, 61.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Location: \n" + this.playerLocation, 5.0f, 30.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "PAUSE", 195.0f, 90.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) " STATS", 195.0f, 65.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) " MAIN\n MENU", 195.0f, 45.0f);
                this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "  EXIT", 195.0f, 15.0f);
                if (this.show_inventory) {
                    this.font.draw((Batch) this.game.getBatch(), (CharSequence) "INVENTORY", 85.0f, 90.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Med-kit\n" + this.playerMedkit, 55.0f, 70.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Antidote\n" + this.playerAntkti, 55.0f, 45.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Revival-kit\n" + this.playerEmgkti, 55.0f, 20.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Adrenaline\n" + this.playerAddrenaline, 100.0f, 70.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Repair-Kits\n" + this.playerRepairKits, 100.0f, 45.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Fortify\n" + this.playerFortify, 100.0f, 20.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Traps\n" + this.playerTraps, 145.0f, 70.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Rifle\n0", 145.0f, 45.0f);
                    this.menuLabel.draw((Batch) this.game.getBatch(), (CharSequence) "Shotgun\n0", 145.0f, 20.0f);
                }
                else if (this.show_stats) {
                    this.font.draw((Batch) this.game.getBatch(), (CharSequence) "PLAYER STATS", 80.0f, 90.0f);
                }
                this.menuLabel.getData().setScale(0.7f);
            }
        }
        this.game.getBatch().end();
    }

    public void render(float delta) {
        ScreenUtils.clear(Color.BLACK);
        Gdx.gl.glEnable(GL20.GL_BLEND);
        Gdx.gl.glBlendFunc(GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);
        controllerUpdate();
        jsonUpdate();
        debugDraw();
        gameClock += Gdx.graphics.getDeltaTime();

        Gdx.app.log("AndroidTouch", "Game Clock : " + gameClock );


        if (this.touchPad_4_touched) {
            Gdx.app.exit();
        }
        if (this.touchPad_2_touched) {
            this.touchpad_3_counter += 1;
            if (this.touchpad_3_counter == 1) {
                this.show_inventory = false;
                this.show_stats = true;
                capturedTime = gameClock;
                Gdx.app.log("AndroidTouch", "Captured Time : " + capturedTime);
            }
            if (this.touchpad_3_counter >= 2 && gameClock - capturedTime > 2) {
                this.show_stats = false;
                this.show_inventory = true;
                this.touchpad_3_counter = 0;
            }
        }
        Gdx.app.log("JSON:", this.json.prettyPrint(this.jsonString));
        this.stage.act(Math.min(Gdx.graphics.getDeltaTime(), 0.033333335f));
        this.stage.draw();
    }

    public void resize(int width, int height) {
        this.viewport.update(width, height, true);
        this.stage.getViewport().update(width, height, true);
    }

    public void pause() {
        super.pause();
    }

    public void resume() {
        super.resume();
    }

    public void hide() {
        super.hide();
    }

    public void dispose() {
        super.dispose();
        Gdx.input.setInputProcessor((InputProcessor) null);
        this.stage.dispose();
    }

    public void DrawDebugLine(Vector2 start, Vector2 end, int lineWidth, Color color, Matrix4 projectionMatrix) {
        Gdx.gl.glLineWidth((float) lineWidth);
        this.debugRender.setProjectionMatrix(projectionMatrix);
        this.debugRender.begin(ShapeRenderer.ShapeType.Line);
        this.debugRender.setColor(color);
        this.debugRender.line(start, end);
        this.debugRender.end();
        Gdx.gl.glLineWidth(1.0f);
    }

    public void DrawDebugSquare(Vector2 start, Vector2 end, Color color, Matrix4 projectionMatrix) {
        this.debugRender.setProjectionMatrix(projectionMatrix);
        this.debugRender.begin(ShapeRenderer.ShapeType.Filled);
        this.debugRender.setColor(color);
        this.debugRender.rect(start.x, start.y, end.x, end.y);
        this.debugRender.end();
    }

    public String searchForConnection() {
        DatagramSocket testSocket = null;
        int i = 2;
        String subnet = null;
        while (!this.testConnection && (i = i + 1) <= 254) {
            subnet = "192.168.2." + i;
            Gdx.app.log("AndroidNetwork", "TESTING Connection... " + subnet);
            try {
                testSocket = new DatagramSocket();
                testSocket.setSoTimeout(100);
                byte[] buffer = new byte[1024];
                testSocket.connect(InetAddress.getByName(subnet), 5500);
                byte[] t = "Client Packet TEST".getBytes();
                testSocket.send(new DatagramPacket(t, t.length));
                DatagramPacket testReceivePacket = new DatagramPacket(buffer, buffer.length);
                testSocket.receive(testReceivePacket);
                String testReceivePacketString = removeNonAlphanumeric(new String(testReceivePacket.getData()));
                if (!testReceivePacketString.equals("")) {
                    Gdx.app.log("AndroidNetwork", "TEST Connected!!!");
                    this.testConnection = true;
                } else {
                    this.testConnection = false;
                }
                Gdx.app.log("AndroidNetwork", testReceivePacket.getSocketAddress().toString());
                Gdx.app.log("AndroidNetwork", testReceivePacketString);
                if (removeNonAlphanumeric(new String(testReceivePacket.getData())).length() > 0) {
                    Gdx.app.log("AndroidNetwork", "TEST GOOD TO GO !!!!");
                } else {
                    Gdx.app.log("AndroidNetwork", "TEST NO GO !!!!");
                }
            } catch (SocketException e) {
                System.out.println("Socket: " + e.getMessage());
                if (testSocket == null) {
                }
            } catch (IOException e2) {
                System.out.println("IO: " + e2.getMessage());
                if (testSocket != null) {
                }
            } catch (Throwable th) {
                if (testSocket != null) {
                    testSocket.close();
                }
                throw th;
            }
            testSocket.close();
        }
        return subnet;
    }
}
