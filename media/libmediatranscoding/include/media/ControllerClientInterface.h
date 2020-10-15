/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_MEDIA_CONTROLLER_CLIENT_INTERFACE_H
#define ANDROID_MEDIA_CONTROLLER_CLIENT_INTERFACE_H

#include <aidl/android/media/ITranscodingClientCallback.h>
#include <aidl/android/media/TranscodingRequestParcel.h>
#include <media/TranscodingDefs.h>

namespace android {

using ::aidl::android::media::ITranscodingClientCallback;
using ::aidl::android::media::TranscodingRequestParcel;

// Interface for a client to call the controller to schedule or retrieve
// the status of a session.
class ControllerClientInterface {
public:
    /**
     * Submits one request to the controller.
     *
     * Returns true on success and false on failure. This call will fail is a session identified
     * by <clientId, sessionId> already exists.
     */
    virtual bool submit(ClientIdType clientId, SessionIdType sessionId, uid_t uid,
                        const TranscodingRequestParcel& request,
                        const std::weak_ptr<ITranscodingClientCallback>& clientCallback) = 0;

    /**
     * Cancels a session identified by <clientId, sessionId>.
     *
     * If sessionId is negative (<0), all sessions with a specified priority (that's not
     * TranscodingSessionPriority::kUnspecified) will be cancelled. Otherwise, only the single
     * session <clientId, sessionId> will be cancelled.
     *
     * Returns false if a single session is being cancelled but it doesn't exist. Returns
     * true otherwise.
     */
    virtual bool cancel(ClientIdType clientId, SessionIdType sessionId) = 0;

    /**
     * Retrieves information about a session.
     *
     * Returns true and the session if it exists, and false otherwise.
     */
    virtual bool getSession(ClientIdType clientId, SessionIdType sessionId,
                            TranscodingRequestParcel* request) = 0;

protected:
    virtual ~ControllerClientInterface() = default;
};

}  // namespace android
#endif  // ANDROID_MEDIA_CONTROLLER_CLIENT_INTERFACE_H
