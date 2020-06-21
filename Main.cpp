
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	// ウィンドウタイトルを指定
	Window::SetTitle(U"Wide Putin");
	// ウィンドウのフレームを非表示にする
	Window::SetStyle(WindowStyle::Frameless);
	// Wide Putin の音声ファイルを用意, 速度 1.0
	const Audio audio(Resource(U"assets/putin.m4a"));
	audio.play();
	FFTResult fft;
	double speed = 1.0;
	// フォントを用意
	const Font font(60, Typeface::Default, FontStyle::Italic);
	const Font fontPos(30);
	// プーチンのテクスチャを用意
	const Texture putin(Resource(U"assets/putin.png"));
	audio.setVolume(0.5);
	const String text = U"Wide Putin https://github.com/yudete/wideputin";
	while (System::Update())
	{
		// テキストを画面の中心に描く
		font(U"Wide Putin").drawAt(Scene::Center(), Palette::Black);
		// 座標決め用
		fontPos(U"x: {} y: {}"_fmt(Cursor::Pos().x, Cursor::Pos().y)).drawAt(Vec2(640, 580));
		if (audio.isPlaying())
		{
			// FFT 解析
			FFT::Analyze(fft, audio);

			// 結果を可視化
			for (auto i : step(800))
			{
				const double size = Pow(fft.buffer[i], 0.6f) * 1000;
				RectF(Arg::bottomLeft(i, 480), 1, size).draw(HSV(240 - i));
			}

			// 周波数表示
			// Rect(Cursor::Pos().x, 0, 1, Scene::Height()).draw();
			// ClearPrint();
			// Print << U"{} Hz"_fmt(Cursor::Pos().x * fft.resolution);
		}
		// プーチンの画像をマウスカーソルに追従させて描画する
		putin.scaled(0.5).draw(Cursor::Pos());
		// 再生中なら「Pause」ボタン
		if (audio.isPlaying())
		{
			if (SimpleGUI::Button(U"一時停止", Vec2(20, 20), 120))
			{
				audio.pause();
			}
		}
		else // 停止中なら「Play」ボタン
		{
			if (SimpleGUI::Button(U"再生", Vec2(20, 20), 120))
			{
				audio.play();
			}
		}
		if (SimpleGUI::Button(U"リセット", Vec2(464, 330)))
		{
			// 再生速度を 1.0 に変更, スライダーをリセット
			speed = 1.0;
			audio.setSpeed(1.0);
		}
		if (SimpleGUI::Slider(U"{:.2f}"_fmt(speed), speed, 0.1, 2.0, Vec2(256,330)))
		{
			// 再生スピードを設定 (0.1 - 2.0)
			audio.setSpeed(speed);
		}
		if (SimpleGUI::Button(U"閉じる", Vec2(680, 20)))
		{
			// 閉じる
			System::Exit();
		}
		if (SimpleGUI::Button(U"ツイート", Vec2(20, 560)))
		{
			// text をつぶやくツイート投稿画面を開く
			Twitter::OpenTweetWindow(text);
		}

	}
}