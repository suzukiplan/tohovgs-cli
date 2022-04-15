/*
MIT License
Copyright (c) 2022 Yoji Suzuki

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
const fs = require('fs').promises;
require('date-utils');

const version = new Date().toFormat('YYYY.MM.DD')
const songListPath = '../mml/songlist.json';
const versionPath = '../mml/songlist.ver';
const targetId = process.argv.length < 3 ? undefined : process.argv[2];
const csvPath = '../playlist.csv';

async function updateSongList() {
    const songListJson = await fs.readFile(songListPath);
    const songList = JSON.parse(songListJson);
    if (songList.version == version) {
        console.error(`songlist.json was not updated. (same version: ${version})`)
    } else {
        console.log(`updating songlist version: ${songList.version} -> ${version}`);
        songList.version = version;
        await fs.writeFile(songListPath, JSON.stringify(songList, undefined, 4));
        await fs.writeFile(versionPath, `${version}\n`);
    }
    return songList
}

function searchSong(songList, targetId) {
    for (var i = 0; i < songList.albums.length; i++) {
        for (var j = 0; j < songList.albums[i].songs.length; j++) {
            const song = songList.albums[i].songs[j];
            if (targetId.startsWith(song.mml)) {
                return song;
            }
        }
    }
}

async function updatePlayList(songList, targetId) {
    const song = searchSong(songList, `${targetId}`);
    if (song) {
        const record = `mml/${targetId}.mml, ${song.loop}, ${song.name}\n`
        console.log(`Appending ${targetId} to the playlist`);
        const csv = await fs.readFile(csvPath);
        await fs.writeFile(csvPath, csv + record);
    } else {
        console.error(`playlist.csv was not updated. (songId "${targetId}" was not found)`)
    }
}

(async () => {
    const songList = await updateSongList();
    if (songList && targetId) {
        await updatePlayList(songList, targetId);
    }
})();
