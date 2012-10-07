/** @file
  * @copyright Copyright (c) 2012 PROFACTOR GmbH. All rights reserved. 
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are
  * met:
  *
  *     * Redistributions of source code must retain the above copyright
  * notice, this list of conditions and the following disclaimer.
  *     * Redistributions in binary form must reproduce the above
  * copyright notice, this list of conditions and the following disclaimer
  * in the documentation and/or other materials provided with the
  * distribution.
  *     * Neither the name of Google Inc. nor the names of its
  * contributors may be used to endorse or promote products derived from
  * this software without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  * @authors christoph.kopf@profactor.at
  *          florian.eckerstorfer@profactor.at
  */
  
#ifndef REME_SDK_INITIALIZER_H
#define REME_SDK_INITIALIZER_H

#pragma once

#include "types.h"

#include <QObject>

#include <reconstructmesdk/types.h>

// FoWrward declarations
class QImage;

namespace ReconstructMeGUI {

  /** This class provides scanning utilities */
  class reme_sdk_initializer : public QObject 
  {  
    Q_OBJECT;
    
  public:
    reme_sdk_initializer(reme_context_t c);
    ~reme_sdk_initializer();

  public slots:
    void initialize(init_t what);

    const reme_context_t context() const;
    const reme_sensor_t sensor() const;
    const reme_volume_t volume() const;

    /** Getter for correct sized RGB QImage */
    const QImage *rgb_image() const;
    /** Getter for correct sized Phong QImage */
    const QImage *phong_image() const;
    /** Getter for correct sized Depth QImage */
    const QImage *depth_image() const;

    /** Getter for correct sized RGB QImage */
    QImage *rgb_image();
    /** Getter for correct sized Phong QImage */
    QImage *phong_image();
    /** Getter for correct sized Depth QImage */
    QImage *depth_image();

  signals:
    void initializing(init_t what);
    void initialized(init_t what, bool success);
    void sdk_initialized();
    void initialized_images();

  private:
    bool try_open_sensor(const char *driver);
    
    bool open_sensor();
    bool compile_context();
    bool apply_license();

    reme_context_t _c;
    reme_sensor_t _s;
    reme_volume_t _v;

    QImage* _rgb_image;
    QImage* _phong_image;
    QImage* _depth_image;

    bool _has_compiled_context;
    bool _has_sensor;
    bool _has_volume;
  };
}

#endif // REME_SDK_INITIALIZER_H