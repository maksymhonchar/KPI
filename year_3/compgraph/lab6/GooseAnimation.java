package com.maxdev;

import javax.vecmath.*;
import com.sun.j3d.utils.universe.*;
import javax.media.j3d.*;
import com.sun.j3d.utils.behaviors.vp.*;
import javax.swing.JFrame;
import com.sun.j3d.loaders.*;
import com.sun.j3d.loaders.objectfile.*;
import java.util.Hashtable;
import java.util.Enumeration;

public class GooseAnimation extends JFrame {
	public Canvas3D myCanvas3D;

	public GooseAnimation() {
		// механізм для закриття вікна та виходу з програми
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// параметри перегляду сцени за замовчанням
		myCanvas3D = new Canvas3D(SimpleUniverse.getPreferredConfiguration());
		// створення SimpleUniverse (віртуального всесвіту)
		SimpleUniverse simpUniv = new SimpleUniverse(myCanvas3D);
		// положення глядача за замовчанням
		simpUniv.getViewingPlatform().setNominalViewingTransform();
		// створення сцени
		createSceneGraph(simpUniv);
		// додання світла у сцену
		addLight(simpUniv);
		// наступні рядки дозволяють навігацію по сцені за допомогою миші
		OrbitBehavior ob = new OrbitBehavior(myCanvas3D);
		ob.setSchedulingBounds(new BoundingSphere(new Point3d(0.0, 0.0, 0.0), Double.MAX_VALUE));
		simpUniv.getViewingPlatform().setViewPlatformBehavior(ob);
		// параметри вікна програми
		setTitle("Goose");
		setSize(700, 700);
		getContentPane().add("Center", myCanvas3D);
		setVisible(true);
	}

	public static void main(String[] args) {
		GooseAnimation gooseAnimation = new GooseAnimation();
	}

	// в цьому методі створюються об'єкти та додаються до сцени
	public void createSceneGraph(SimpleUniverse su) {
		// завантаження файлу .obj.
		ObjectFile f = new ObjectFile(ObjectFile.RESIZE);
		Scene gooseScene = null;
		try {
			gooseScene = f.load("goose.obj");
		} catch (Exception e) {
			System.out.println("File loading failed:" + e);
		}
		// створення трансформаційної групи для завнтаженого будильника
		Transform3D tfGoose = new Transform3D();
		tfGoose.rotZ(0);
		tfGoose.rotY(Math.PI / 2);
		tfGoose.setScale(1.0 / 3);
		tfGoose.setTranslation(new Vector3d(-0.5f, 0.0f, 0.0f));
		TransformGroup tgGoose = new TransformGroup(tfGoose);
		// отримання імен об'єктів, з яких складаються будильник та стіл
		// та вивід в консоль назв об'єктів, з яких складається стіл
		Hashtable gooseNamedObjects = gooseScene.getNamedObjects();
		Enumeration enumer = gooseNamedObjects.keys();
		String name;
		while (enumer.hasMoreElements()) {
			name = (String) enumer.nextElement();
			System.out.println("Name: " + name);
		}

		// пофарбуємо тіло гуся у сірий колір
		Appearance bodyApp = new Appearance();
		setToMyDefaultAppearance(bodyApp, new Color3f(0.6f, 0.6f, 0.6f));
		Shape3D body = (Shape3D) gooseNamedObjects.get("body");
		body.setAppearance(bodyApp);

		// пофарбуємо ніс та ноги гуся у помаранчевий колір
		Appearance orangeApp = new Appearance();
		setToMyDefaultAppearance(orangeApp, new Color3f(250 / 255f, 160 / 255f, 9 / 255f));
		Shape3D beak = (Shape3D) gooseNamedObjects.get("beak");
		Shape3D legLeft = (Shape3D) gooseNamedObjects.get("left_leg");
		Shape3D legRight = (Shape3D) gooseNamedObjects.get("right_leg");
		legLeft.setAppearance(orangeApp);
		legRight.setAppearance(orangeApp);
		beak.setAppearance(orangeApp);

		Shape3D[] goose = new Shape3D[] { body, beak };
		for (Shape3D shape : goose) {
			tgGoose.addChild(shape.cloneTree());
		}
		// група трансформації лівої ноги
		TransformGroup tgLeftLeg = new TransformGroup();
		tgLeftLeg.addChild(legLeft.cloneTree());
		// повернемо площину обертання на 90 градусів відносно осі Z
		Transform3D leftLegRotationAxis = new Transform3D();
		leftLegRotationAxis.rotZ(Math.PI / 2);
		int timeStart = 500; // стрілка почне рух через 2 секунди після запуску програми
		int timeRotationHour = 500;// час одного оберту
		// Alpha для руху годинної стрілки
		Alpha leftLegRotationAlpha = new Alpha(-1, Alpha.INCREASING_ENABLE | Alpha.DECREASING_ENABLE, timeStart, 0,
				timeRotationHour, 0, 0, timeRotationHour, 0, 0);
		// обертання годинної стрілки
		RotationInterpolator leftLegRotation = new RotationInterpolator(leftLegRotationAlpha, tgLeftLeg,
				leftLegRotationAxis, (float) Math.PI / 4, 0.0f);
		BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), Double.MAX_VALUE);
		leftLegRotation.setSchedulingBounds(bounds);
		tgLeftLeg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tgLeftLeg.addChild(leftLegRotation);

		// група трансформації правої ноги
		TransformGroup tgRightLeg = new TransformGroup();
		tgRightLeg.addChild(legRight.cloneTree());
		// повернемо площину обертання на 90 градусів відносно осі Z
		Transform3D rightLegRotationAxis = new Transform3D();
		rightLegRotationAxis.rotZ(Math.PI / 2);
		// Alpha для руху годинної стрілки
		Alpha rightLegRotationAlpha = new Alpha(-1, Alpha.INCREASING_ENABLE | Alpha.DECREASING_ENABLE, 0, 0,
				timeRotationHour, 0, 0, timeRotationHour, 0, 0);
		// обертання годинної стрілки
		RotationInterpolator rightLegRotation = new RotationInterpolator(rightLegRotationAlpha, tgRightLeg,
				rightLegRotationAxis, (float) Math.PI / 4, 0.0f);
		rightLegRotation.setSchedulingBounds(bounds);
		tgRightLeg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tgRightLeg.addChild(rightLegRotation);

		// розміщуємо гуся
		Transform3D tfRotor = new Transform3D();
		Transform3D tfRotor2 = new Transform3D();
		tfRotor.rotZ(-Math.PI / 8);
		tfRotor2.rotY(Math.PI / 2);// розміщуємо у напівоберті до користувача
		tfRotor.mul(tfRotor2);
		tfRotor.setScale(1.0 / 3);
		tfRotor.setTranslation(new Vector3d(-0.5f, 0.0f, 0.0f));// переміщуємо
		TransformGroup tgGooseLegs = new TransformGroup(tfRotor);
		tgGooseLegs.addChild(tgRightLeg);
		tgGooseLegs.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tgGooseLegs.addChild(tgLeftLeg);

		// створення сцени
		BranchGroup theScene = new BranchGroup();

		Transform3D gooseRotationAxis = new Transform3D();
		Transform3D gooseRotationAxis2 = new Transform3D();
		gooseRotationAxis.rotX(Math.PI);
		TransformGroup group = new TransformGroup();
		long crawlTime = 5000;// час, за який тарган переповзе екран
		Alpha crawlAlpha = new Alpha(-1, Alpha.INCREASING_ENABLE | Alpha.DECREASING_ENABLE, 0, 0, crawlTime, 0, 0,
				crawlTime, 0, 0);
		float crawlDistance = 1.0f; // відстань, на яку просунеться об’єкт

		Alpha gooseRotationAlpha = new Alpha(-1, Alpha.INCREASING_ENABLE | Alpha.DECREASING_ENABLE, crawlTime, 0, 0, 0,
				crawlTime, 0, 0, crawlTime);
		RotationInterpolator gooseRotation = new RotationInterpolator(gooseRotationAlpha, group, gooseRotationAxis,
				0.0f, (float) Math.PI);
		PositionInterpolator posICrawl = new PositionInterpolator(crawlAlpha, group, gooseRotationAxis, 0.0f,
				crawlDistance);
		posICrawl.setSchedulingBounds(bounds);
		gooseRotation.setSchedulingBounds(bounds);
		group.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		// group.addChild(posICrawl);
		// group.addChild(gooseRotation);

		group.addChild(tgGoose);
		group.addChild(tgGooseLegs);
		theScene.addChild(group);
		// створюємо что чорний фон
		Background bg = new Background(new Color3f(0.0f, 0.0f, 0.0f));
		bg.setApplicationBounds(bounds);
		theScene.addChild(bg);
		theScene.compile();
		// додаємо сцену до віртуального всесвіту
		su.addBranchGraph(theScene);
	}

	// метод для генерації зовнішньої поверхні
	public static void setToMyDefaultAppearance(Appearance app, Color3f col) {
		app.setMaterial(new Material(col, col, col, col, 150.0f));
	}

	// метод для додавання освітлення
	public void addLight(SimpleUniverse su) {
		BranchGroup bgLight = new BranchGroup();
		BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 100.0);
		Color3f lightColour1 = new Color3f(1.0f, 1.0f, 1.0f);
		Vector3f lightDir1 = new Vector3f(-1.0f, 0.0f, -0.5f);
		DirectionalLight light1 = new DirectionalLight(lightColour1, lightDir1);
		light1.setInfluencingBounds(bounds);
		bgLight.addChild(light1);
		su.addBranchGraph(bgLight);
	}
}
