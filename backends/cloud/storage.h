/* ScummVM - Graphic Adventure Engine
*
* ScummVM is the legal property of its developers, whose names
* are too numerous to list here. Please refer to the COPYRIGHT
* file distributed with this source distribution.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#ifndef BACKENDS_CLOUD_STORAGE_H
#define BACKENDS_CLOUD_STORAGE_H

#include "backends/cloud/storagefile.h"
#include "backends/cloud/storageinfo.h"
#include "backends/networking/curl/request.h"
#include "backends/networking/curl/curlrequest.h"
#include "common/array.h"
#include "common/callback.h"
#include "common/mutex.h"
#include "common/stream.h"
#include "common/str.h"

namespace Cloud {

class SavesSyncRequest;

class Storage {
public:
	typedef Networking::Response<Common::Array<StorageFile>&> FileArrayResponse;
	typedef Networking::Response<StorageInfo> StorageInfoResponse;
	typedef Networking::Response<bool> BoolResponse;
	typedef Networking::Response<StorageFile> UploadResponse;
	typedef Networking::Response<Common::Array<StorageFile> &> ListDirectoryResponse;

	typedef Common::BaseCallback<FileArrayResponse> *FileArrayCallback;
	typedef Common::BaseCallback<StorageInfoResponse> *StorageInfoCallback;
	typedef Common::BaseCallback<BoolResponse> *BoolCallback;
	typedef Common::BaseCallback<UploadResponse> *UploadCallback;
	typedef Common::BaseCallback<ListDirectoryResponse> *ListDirectoryCallback;

protected:
	/** Keeps track of running requests. */
	uint32 _runningRequestsCount;
	Common::Mutex _runningRequestsMutex;
	SavesSyncRequest *_savesSyncRequest;

	/** Returns default error callback (printErrorResponse). */
	virtual Networking::ErrorCallback getErrorPrintingCallback();

	/** Prints ErrorResponse contents with debug(). */
	virtual void printErrorResponse(Networking::ErrorResponse error);

	/**
	 * Adds request to the ConnMan, but also increases _runningRequestsCount.
	 * This method should be used by Storage implementations instead of
	 * direct ConnMan.addRequest() call.
	 *
	 * @return the same Request pointer, just as a shortcut
	 */
	virtual Networking::Request *addRequest(Networking::Request *request);

	/**
	 * Decreases _runningRequestCount. It's called from ConnMan automatically.
	 * Passed pointer is dangling, but one can use the address to determine
	 * some special Requests (which addresses were remembered somewhere).
	 */
	virtual void requestFinishedCallback(Networking::Request *invalidRequestPointer);

public:
	Storage();
	virtual ~Storage();

	/**
	 * Storage methods, which are used by CloudManager to save
	 * storage in configuration file.
	 */

	/**
	 * Save storage data using ConfMan.
	 * @param keyPrefix all saved keys must start with this prefix.
	 * @note every Storage must write keyPrefix + "type" key
	 *       with common value (e.g. "Dropbox").
	 */
	virtual void saveConfig(Common::String keyPrefix) = 0;

	/**
	 * Public Cloud API comes down there.
	 *
	 * All Cloud API methods return Networking::Request *, which
	 * might be used to control request. All methods also accept
	 * a callback, which is called, when request is complete.
	 */

	/** Returns ListDirectoryStatus struct with list of files. */
	virtual Networking::Request *listDirectory(Common::String path, ListDirectoryCallback callback, Networking::ErrorCallback errorCallback, bool recursive = false) = 0;
	
	/** Returns UploadStatus struct with info about uploaded file. */
	virtual Networking::Request *upload(Common::String path, Common::SeekableReadStream *contents, UploadCallback callback, Networking::ErrorCallback errorCallback) = 0;
	virtual Networking::Request *upload(Common::String remotePath, Common::String localPath, UploadCallback callback, Networking::ErrorCallback errorCallback);

	/** Returns pointer to Networking::NetworkReadStream. */
	virtual Networking::Request *streamFile(Common::String path, Networking::NetworkReadStreamCallback callback, Networking::ErrorCallback errorCallback) = 0;

	/** Calls the callback when finished. */
	virtual Networking::Request *download(Common::String remotePath, Common::String localPath, BoolCallback callback, Networking::ErrorCallback errorCallback);

	/** Returns Common::Array<StorageFile> with list of files, which were not downloaded. */
	virtual Networking::Request *downloadFolder(Common::String remotePath, Common::String localPath, FileArrayCallback callback, Networking::ErrorCallback errorCallback, bool recursive = false);

	/** Calls the callback when finished. */
	virtual Networking::Request *remove(Common::String path, BoolCallback callback, Networking::ErrorCallback errorCallback) = 0;

	/** Calls the callback when finished. */
	virtual SavesSyncRequest *syncSaves(BoolCallback callback, Networking::ErrorCallback errorCallback);

	/** Calls the callback when finished. */
	virtual Networking::Request *createDirectory(Common::String path, BoolCallback callback, Networking::ErrorCallback errorCallback) = 0;

	/** Returns the StorageInfo struct. */
	virtual Networking::Request *info(StorageInfoCallback callback, Networking::ErrorCallback errorCallback) = 0;

	/** Returns storage's saves directory path with the trailing slash. */
	virtual Common::String savesDirectoryPath() = 0;

	/** Returns whether there are any requests running. */
	virtual bool isWorking();

	/** Returns whether there is a SavesSyncRequest running. */
	virtual bool isSyncing();

	/** Returns a number in [0, 1] range which represents current sync progress (1 = complete). */
	virtual double getSyncProgress();

	/** Returns an array of saves names which are not yet synced (thus cannot be used). */
	virtual Common::Array<Common::String> getSyncingFiles();
};

} // End of namespace Cloud

#endif
