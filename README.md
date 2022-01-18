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

`make` を実行すると 東方 VGS のプレイリスト（[playlist.csv](playlist.csv)）を **シャッフル & 繰り返し** の設定で 1 曲づつ再生します。

```bash
% make
./tohovgs -s -i playlist.csv
Playing mml/BSLOT034.mml ネクロファンタジア ... OK
Playing mml/BSLOT003.mml ルーネイトエルフ ... OK
Playing mml/BSLOT062.mml 不思議の国のアリス ... OK
Playing mml/BSLOT080.mml Witching Dream ... OK
Playing mml/BSLOT004.mml おてんば恋娘 ... OK
Playing mml/BSLOT082.mml 装飾戦　〜 Decoration Battle ... OK
Playing mml/BSLOT090.mml 運命のダークサイド ... OK
Playing mml/BSLOT047.mml 恋色マスタースパーク ... OK
Playing mml/BSLOT026.mml 東方妖々夢　〜 Ancient Temple ... OK
Playing mml/BSLOT045.mml 永夜の報い　〜 Imperishable Night. ... OK
Playing mml/BSLOT101.mml 緑眼のジェラシー ... OK
：
```

## How to update

```bash
git pull
```

## How to use

### Basic usage

```bash
./tohovgs playlist.csv
```

### Advanced usage

#### (Infinite play)

`-i` オプションを付ければ、リストの再生が全部終わると再びリストの先頭から再生します。

```bash
./tohovgs -i playlist.csv
```

#### (Shuffle play)

`-s` オプションを付ければ、適当にバラけさせて再生します。

```bash
./tohovgs -s playlist.csv
```

> `-i` と `-s` の両方を指定すれば、リストが先頭に戻る都度毎回シャッフルが行われます。

#### (Single MML file play)

```bash
./tohovgs music.mml
```

デフォルトでは無限にループ再生しますが、mml ファイルの後に数字を付与することで指定回数ループ再生後コマンドラインに復帰します。

```bash
./tohovgs music.mml 3
```

#### Customize playlist

[プレイリスト](playlist.csv) のカスタマイズは簡単にできます。

#### Customize MML

MML の仕様は[こんな感じ](https://github.com/suzukiplan/vgs-mml-compiler/blob/master/MML-ja.md)です。

## Omake

- [playlist-wtc1.csv](playlist-wtc1.csv): 平均律クラヴィーア曲集 第 1 巻（J.S.Bach）**未完成**
- [playlist-goldberg.csv](playlist-goldberg.csv): ゴールベルク変奏曲（J.S.Bach）**未完成**
- [playlist-suzuki.csv](playlist-suzuki.csv): 私の自作曲

## License

- 楽曲（東方 Project）著作権: 楽曲の著作権は上海アリス幻樂団に帰属します
- データ著作権: 楽曲データの著作権は Yoji Suzuki に帰属する東方 Project 二次創作物です
- [vgs-bgm-decoder](https://github.com/suzukiplan/vgs-bgm-decoder): このプログラムの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- [vgs-mml-compiler](https://github.com/suzukiplan/vgs-mml-compiler): このプログラムの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- tohovgs-cli: 本プログラムの著作権は Yoji Suzuki に帰属します（MIT ライセンス）
