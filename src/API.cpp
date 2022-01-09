#include "API.hpp"

#include "Paths.hpp"

#include "CustomTypes/SongLoader.hpp"
#include "CustomBeatmapLevelLoader.hpp"

namespace RuntimeSongLoader::API {

    void RefreshSongs() {
        RefreshSongs(true, nullptr);
    }

    void RefreshSongs(bool fullRefresh, const std::function<void(const std::vector<GlobalNamespace::CustomPreviewBeatmapLevel*>&)>& songsLoaded) {
        SongLoader::GetInstance()->RefreshSongs(fullRefresh, songsLoaded);
    }

    void RefreshPacks(bool includeDefault) {
        SongLoader::GetInstance()->RefreshLevelPacks(includeDefault);
    }

    void AddSongsLoadedEvent(const std::function<void(const std::vector<GlobalNamespace::CustomPreviewBeatmapLevel*>&)>& event) {
        SongLoader::AddSongsLoadedEvent(event);
    }

    void AddRefreshLevelPacksEvent(const std::function<void(SongLoaderBeatmapLevelPackCollectionSO*)>& event) {
        SongLoader::AddRefreshLevelPacksEvent(event);
    }

    void AddBeatmapDataLoadedEvent(const std::function<void(CustomJSONData::CustomLevelInfoSaveData*, const std::string&, GlobalNamespace::BeatmapData*)>& event) {
        CustomBeatmapLevelLoader::AddBeatmapDataLoadedEvent(event);
    }

    void DeleteSong(std::string_view path, const std::function<void()>& finished) {
        SongLoader::GetInstance()->DeleteSong(path, finished);
    }

    std::vector<GlobalNamespace::CustomPreviewBeatmapLevel*> GetLoadedSongs() {
        return SongLoader::GetInstance()->GetLoadedLevels();
    }

    bool HasLoadedSongs() {
        return SongLoader::GetInstance()->HasLoaded;
    }

    float GetLoadingProgress()
    {
        auto instance = SongLoader::GetInstance();
        return (float)instance->CurrentFolder / (float)instance->MaxFolders;
    }

    std::optional<GlobalNamespace::CustomPreviewBeatmapLevel*> GetLevelByHash(std::string hash) {
        std::transform(hash.begin(), hash.end(), hash.begin(), toupper);
        for(auto& song : RuntimeSongLoader::API::GetLoadedSongs()) {
            if(to_utf8(csstrtostr(song->levelID)).ends_with(hash))
                return song;
        }
        return std::nullopt;
    }

    std::optional<GlobalNamespace::CustomPreviewBeatmapLevel*> GetLevelById(std::string_view levelID) {
        for(auto& song : RuntimeSongLoader::API::GetLoadedSongs()) {
            if(to_utf8(csstrtostr(song->levelID)) == levelID)
                return song;
        }
        return std::nullopt;
    }

    std::string GetCustomLevelsPrefix() {
        return CustomLevelPrefixID;
    }
    
    std::string GetCustomLevelPacksPrefix() {
        return CustomLevelPackPrefixID;
    }

    std::string GetCustomLevelsPath() {
        return GetBaseLevelsPath() + CustomLevelsFolder + "/";
    }

    std::string GetCustomWIPLevelsPath() {
        return GetBaseLevelsPath() + CustomWIPLevelsFolder + "/";
    }
}