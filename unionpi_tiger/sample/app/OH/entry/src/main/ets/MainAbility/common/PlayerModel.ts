
/*
 * Copyright 2023 Unionman Technology Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

import media from '@ohos.multimedia.media';
import audio from '@ohos.multimedia.audio';
import fileIo from '@ohos.fileio'

export
class Playlist {
    constructor() {
    }

    audioFiles = [];
}

export
class Song {
    public name;
    public fileUri;
    public duration;
    constructor(name, fileUri, duration) {
        this.name = name;
        this.fileUri = fileUri;
        this.duration = duration;
    }
}

export default class PlayerModel {
    isPlaying = false;
    playlist = new Playlist;
    index;
    #player;
    #statusChangedListener;
    #playingProgressListener;
    #intervalID;
    #currentTimeMs;
    #durationTimeMs;
    #volume;

    constructor() {
        this.#player = media.createAudioPlayer();
        this.initAudioPlayer()
        console.info('MusicPlayer[PlayerModel] createAudioPlayer=' + this.#player);
    }



    initAudioPlayer() {
        console.info('MusicPlayer[PlayerModel] initAudioPlayer begin');
        this.#player.on('error', () => {
            console.error(`MusicPlayer[PlayerModel] player error`);
        });
        this.#player.on('finish', () => {
            console.log('MusicPlayer[PlayerModel] finish() callback is called');
            this.play(0,this.isPlaying);
        });

        this.#player.on('timeUpdate', (newTime) => {
            console.log('MusicPlayer[PlayerModel] timeUpdate() callback is called ');
            this.#currentTimeMs = newTime;
        });
        console.info('MusicPlayer[PlayerModel] initAudioPlayer end');
    }
    release() {
        if (typeof (this.#player) != 'undefined') {
            console.info('MusicPlayer[PlayerModel] player.release begin');
            this.#player.release();
            console.info('MusicPlayer[PlayerModel] player.release end');
            this.#player = undefined;
        }
    }

    restorePlayingStatus(status, callback) {
        console.info('MusicPlayer[PlayerModel] restorePlayingStatus ' + JSON.stringify(status));
        for (var i = 0; i < this.playlist.audioFiles.length; i++) {
            if (this.playlist.audioFiles[i].fileUri === status.uri) {
                console.info('MusicPlayer[PlayerModel] restore to index ' + i);
                this.preLoad(i, () => {
                    this.play(status.seekTo, status.isPlaying);
                    console.info('MusicPlayer[PlayerModel] restore play status');
                    callback(i);
                });
                return;
            }
        }
        console.warn('MusicPlayer[PlayerModel] restorePlayingStatus failed');
        callback(-1);
    }

    getPlaylist(callback) {
        // generate play list
        console.info('MusicPlayer[PlayerModel] generatePlayList');

        console.info('MusicPlayer[PlayerModel] getAudioAssets begin');
        this.playlist = new Playlist();
        this.playlist.audioFiles = [];
        this.playlist.audioFiles[0] = new Song('dynamic.wav', 'system/etc/dynamic.wav', 0);
        this.playlist.audioFiles[1] = new Song('demo.wav', 'system/etc/demo.wav', 0);
        callback()
        console.info('MusicPlayer[PlayerModel] getAudioAssets end');
    }

    setOnStatusChangedListener(callback) {
        this.#statusChangedListener = callback;
    }

    setOnPlayingProgressListener(callback) {
        this.#playingProgressListener = callback;
    }


    notifyPlayingStatus(isPlaying) {
        this.isPlaying = isPlaying;
        this.#statusChangedListener(this.isPlaying);
        console.log('MusicPlayer[PlayerModel] MusicPlayer[PlayerModel] player.currentTime= isPlaying=' + isPlaying + ' intervalId=' + this.#intervalID);
        if (isPlaying) {
            if (typeof (this.#intervalID) === 'undefined') {
                let self = this;
                this.#intervalID = setInterval(() => {
                    if (typeof (self.#playingProgressListener) != "undefined" && self.#playingProgressListener != null) {
                        var timeMs = self.#player.currentTime;
                        //this.#currentTimeMs = timeMs;
                        if (typeof (timeMs) === 'undefined') {
                            timeMs = 0;
                        }
                        console.log('MusicPlayer[PlayerModel] player.currentTime=' + timeMs);
                        self.#playingProgressListener(timeMs);
                    }
                }, 500);
                console.log('MusicPlayer[PlayerModel] set update interval ' + this.#intervalID);
            }
        } else {
            this.cancelTimer();
        }
    }

    cancelTimer() {
        if (typeof (this.#intervalID) != 'undefined') {
            console.log('MusicPlayer[PlayerModel] clear update interval ' + this.#intervalID);
            clearInterval(this.#intervalID);
            this.#intervalID = undefined;
        }
    }

    preLoad(index, callback) {
        console.info('MusicPlayer[PlayerModel] preLoad ' + index + "/" + this.playlist.audioFiles.length);
        if (index < 0 || index >= this.playlist.audioFiles.length) {
            console.error('MusicPlayer[PlayerModel] preLoad ignored');
            return 0;
        }
        this.index = index;

        let uri = this.playlist.audioFiles[index].fileUri
        fileIo.open(uri, (err, fdNumber) => {
            let fdPath = 'fd://'
            let source = fdPath + fdNumber

            if (typeof (source) === 'undefined') {
                console.error('MusicPlayer[PlayerModel] preLoad ignored, source=' + source);
                return;
            }
            console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' begin');
            console.info('MusicPlayer[PlayerModel] state=' + this.#player.state);
            let self = this;

            if (source === this.#player.src && this.#player.state != 'idle') {
                console.info('MusicPlayer[PlayerModel] preLoad finished. src not changed');
                this.#durationTimeMs = this.#player.duration;
                callback();
            } else if (this.#player.state === 'idle') {
                this.#player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.#player.state);
                    this.#durationTimeMs = this.#player.duration;
                    callback();
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                this.#player.src = source;
            } else {
                this.notifyPlayingStatus(false);
                this.cancelTimer();
                console.info('MusicPlayer[PlayerModel] player.reset');
                self.#player.reset();
                console.info('MusicPlayer[PlayerModel] player.reset done, state=' + self.#player.state);
                self.#player.on('dataLoad', () => {
                    console.info('MusicPlayer[PlayerModel] dataLoad callback, state=' + self.#player.state);
                    this.#durationTimeMs = this.#player.duration;
                    callback();
                });
                console.info('MusicPlayer[PlayerModel] player.src=' + source);
                self.#player.src = source;
            }
            console.info('MusicPlayer[PlayerModel] preLoad ' + source + ' end');
        })
    }

    getDurationMs() {
        return this.#durationTimeMs;
    }

    getCurrentMs() {
        return this.#currentTimeMs;
    }

    play(seekTo, startPlay) {
        console.info('MusicPlayer[PlayerModel] play seekTo=' + seekTo + ', startPlay=' + startPlay);
        this.notifyPlayingStatus(startPlay);
        console.info('MusicPlayer[PlayerModel] notifyPlayingStatus play seekTo=' + seekTo + ', startPlay=' + startPlay);
        if (startPlay) {
            if (seekTo < 0 && this.#currentTimeMs > 0) {
                console.info('MusicPlayer[PlayerModel] pop seekTo=' + this.#currentTimeMs);
                seekTo = this.#currentTimeMs;
            }
            let self = this;
            this.#player.on('play', (err, action) => {
                if (err) {
                    console.error(`MusicPlayer[PlayerModel] error returned in play() callback`);
                    return;
                }
                console.log('MusicPlayer[PlayerModel] play() callback entered, player.state=' + self.#player.state);
                if (seekTo > 0) {
                    self.seek(seekTo);
                }
            });
            console.info('MusicPlayer[PlayerModel] call player.play');
            this.#player.play();
            console.info('MusicPlayer[PlayerModel] player.play called player.state=' + this.#player.state);
        } else if (seekTo > 0) {
            this.#playingProgressListener(seekTo);
            this.#currentTimeMs = seekTo;
            console.info('MusicPlayer[PlayerModel] stash seekTo=' + this.#currentTimeMs);
        }
    }

    pause() {
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] pause ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.notifyPlayingStatus(false);
        console.info('MusicPlayer[PlayerModel] call player.pause');
        this.#player.pause();
        console.info('MusicPlayer[PlayerModel] player.pause called, player.state=' + this.#player.state);
    }

    seek(ms) {
        this.#currentTimeMs = ms;
        if (this.isPlaying) {
            console.log('MusicPlayer[PlayerModel] player.seek ' + ms);
            this.#player.seek(ms);
        } else {
            console.log('MusicPlayer[PlayerModel] stash seekTo=' + ms);
        }
    }

    stop() {
        if (!this.isPlaying) {
            console.info('MusicPlayer[PlayerModel] stop ignored, isPlaying=' + this.isPlaying);
            return;
        }
        this.notifyPlayingStatus(false);
        console.info('MusicPlayer[PlayerModel] call player.stop');
        this.#player.stop();
        console.info('MusicPlayer[PlayerModel] player.stop called, player.state=' + this.#player.state);
    }

    async getVolume() {
        let audioManager = audio.getAudioManager();
        this.#volume = await audioManager.getVolume(audio.AudioVolumeType.MEDIA);
        return this.#volume;
    }
    async getMaxVolume() {
        let audioManager = audio.getAudioManager();
        let volume = await audioManager.getMaxVolume(audio.AudioVolumeType.MEDIA);
        return volume;
    }

    async getMinVolume() {
        let audioManager = audio.getAudioManager();
        let volume = await audioManager.getMinVolume(audio.AudioVolumeType.MEDIA);
        return volume;
    }

    async setVolume(volume){
        let audioManager = audio.getAudioManager();
        await audioManager.setVolume(audio.AudioVolumeType.MEDIA,volume);
    }
}