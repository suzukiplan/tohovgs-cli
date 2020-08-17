# 東方 BGM on VGS for コマンドライン

## About

- コマンドライン上で動作する 東方 BGM on VGS です
- 今の所 macOS 専用 です

## How to setup

XCODE をインストール & セットアップ済みの macOS の Terminal で以下のコマンドを実行すれば起動できます。（2 回目以降は `make` のみ実行すれば OK）

```bash
git clone https://github.com/suzukiplan/tohovgs-cli
cd tohovgs-cli
make
```

## How to use

- 現状、[プレイリスト](playlist.csv) の内容を一通りプレイすることしかできません
- [プレイリスト](playlist.csv) のカスタマイズは中身を見れば簡単にできると思われます

## License

- 楽曲（東方 Project）著作権: 楽曲の著作権は上海アリス幻樂団に帰属します
- データ著作権: 楽曲データの著作権は Yoji Suzuki に帰属する東方 Project 二次創作物です
- [vgs-bgm-decoder](https://github.com/suzukiplan/vgs-bgm-decoder): このプログラムの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- [vgs-mml-compiler](https://github.com/suzukiplan/vgs-mml-compiler): このプログラムのの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- [gamepad-osx](https://github.com/suzukiplan/gamepad-osx): このプログラムのの著作権は Yoji Suzuki に帰属します（MIT ライセンス）
- tohovgs-cli: 本プログラムの著作権は Yoji Suzuki に帰属します（MIT ライセンス）
