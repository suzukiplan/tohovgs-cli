# 東方 BGM on VGS for コマンドライン

## About

- コマンドライン上で動作する 東方 BGM on VGS です
- 今の所 macOS 専用 です
- このリポジトリの　[./mml](./mml)　ディレクトリが、東方 BGM on VGS の楽曲配信サーバのデータソースになっているので、最新の楽曲配信の情報はコチラのリポジトリをチェックしていただくのが一番手っ取り早いです
  - 現在の仕込み状況は [Open 中の Pull Request](https://github.com/suzukiplan/tohovgs-cli/pulls) で確認できます
  - 配信済み楽曲の情報は [Closed Pull Request](https://github.com/suzukiplan/tohovgs-cli/pulls?q=is%3Apr+is%3Aclosed) で確認できます
- 楽曲配信サーバの origin は（調べれば分かることですが念の為）非公開です
  - origin にアクセスすると通信料を私が負担する必要があるため、東方BGM on VGS のアプリ外からのアクセスはご遠慮ください
  - 独自のプログラムから楽曲配信サーバにアクセスしたい場合は [gh-pages](https://suzukiplan.github.io/tohovgs-cli/mml/songlist.json) からアクセスする方法もあり、それなら私の通信料負担は発生しないので助かります

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

## License

- 楽曲（東方 Project）著作権: 楽曲の著作権は上海アリス幻樂団に帰属します
- データ著作権: 楽曲データの著作権は Yoji Suzuki に帰属する東方 Project 二次創作物です
  - 本楽曲の東方Projectの二次創作物への利用は [東方Projectの二次創作ガイドライン](https://touhou-project.news/guideline/) で認められている範囲でご自由にお使い頂けます（事前事後の連絡は基本不要ですがご連絡いただければ喜びます）
- [vgs-bgm-decoder](https://github.com/suzukiplan/vgs-bgm-decoder): このプログラムの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- [vgs-mml-compiler](https://github.com/suzukiplan/vgs-mml-compiler): このプログラムの著作権は Yoji Suzuki に帰属します（2 箇条 BSD ライセンス）
- tohovgs-cli: 本プログラムの著作権は Yoji Suzuki に帰属します（MIT ライセンス）
- meta-update: 本プログラムの著作権は Yoji Suzuki に帰属します（MIT ライセンス)
