﻿
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// Wide Putin の音声ファイルを用意
	const Audio audio(U"assets/putin.m4a");
	audio.play();
	double speed = 1.0;
	// 大きさ 60 のフォントを用意
	const Font font(60, Typeface::Default, FontStyle::Italic);
	const Font fontPos(30);
	// プーチンのテクスチャを用意
	const Texture putin(U"assets/putin.png");

	while (System::Update())
	{
		// テキストを画面の中心に描く
		font(U"Wide Putin").drawAt(Scene::Center(), Palette::Black);
		// 座標決め用
		fontPos(U"x: {} y: {}"_fmt(Cursor::Pos().x, Cursor::Pos().y)).drawAt(Vec2(640, 580));

		// プーチンの画像をマウスカーソルに追従させて描画する
		putin.scaled(0.5).draw(Cursor::Pos());
		if (SimpleGUI::Button(U"Play", Vec2(20, 20)))
		{
			// 再生
			audio.play();
		}
		if (SimpleGUI::Button(U"Pause", Vec2(20, 60)))
		{
			// 一時停止
			audio.pause();
		}
		if (SimpleGUI::Slider(U"{:.2f}"_fmt(speed), speed, 0.1, 2.0, Vec2(256,330)))
		{
			// 再生スピードを設定 (0.1 - 2.0)
			audio.setSpeed(speed);
		}
		if (SimpleGUI::Button(U"Reset", Vec2(464, 330)))
		{
			audio.setSpeed(1.0);
		}
	}
}