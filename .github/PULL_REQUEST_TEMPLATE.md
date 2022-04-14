# Pull Request to add a new song to the Touhou VGS

## Check list

- 定形作業
  - [ ] 曲データ作成
  - [ ] songlist.json に {SongRecord} 追加
  - [ ] meta-update 実行
  - [ ] 最終チェック
  - [ ] 配信テスト
- その他
  - n/a
- マージ後作業
  - [ ] YouTube投稿
  - [ ] ブログ投稿
  - [ ] Twitter投稿

## Song Record

```json
{
    "appleId": "123456789",
    "mml": "THxx-xx",
    "ver": 0,
    "loop": 1,
    "name": "日本語",
    "english": "英語"
}
```

## Twitter Submission Manuscript

```text
#東方VGS で #東方星蓮船 より #{曲名} を配信しました。
（一言コメント）
https://suzukiplan.blogspot.com/{article}
```

## YouTube Summary Manuscript

```text
この動画は東方Project二次創作です。東方星蓮船より XXX のテーマ「XXX」をVGSでアレンジしてみました。本作品は、スマートフォンアプリ「東方BGM on VGS」でもお楽しみ頂けます。

【iPhone版】
https://apps.apple.com/jp/app/id680248037

【Android版】
https://play.google.com/store/apps/details?id=com.suzukiplan.TOHOVGS

【macOSコマンドライン版】
https://github.com/suzukiplan/tohovgs-cli

【東方星蓮船の原曲】（AppleMusic）
https://music.apple.com/jp/album/touhou-seirensen-undefined-fantastic-object-soundtrack/1581358392

【SUZUKI PLAN再生リスト】
アルバム配信
https://www.youtube.com/playlist?list=PL7zhksAnez5scHa0NzQNeOz5y6IUIxVmj

新曲配信
https://www.youtube.com/playlist?list=PL7zhksAnez5sFxuCb7P66x6tKh6ifztKz

【SUZUKI PLAN Web Site】
https://suzukiplan.github.io/

【SUZUKI PLAN Blog】
https://suzukiplan.blogspot.com/
```