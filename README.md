# Rhino

[![GitHub release](https://img.shields.io/github/release/Picovoice/Rhino.svg)](https://github.com/Picovoice/Rhino/releases)
[![GitHub](https://img.shields.io/github/license/Picovoice/rhino)](https://github.com/Picovoice/rhino/)

[![Crates.io](https://img.shields.io/crates/v/pv_rhino)](https://crates.io/crates/pv_rhino)<!-- markdown-link-check-disable-line -->
[![Maven Central](https://img.shields.io/maven-central/v/ai.picovoice/rhino-android?label=maven-central%20%5Bandroid%5D)](https://repo1.maven.org/maven2/ai/picovoice/rhino-android/)
[![Maven Central](https://img.shields.io/maven-central/v/ai.picovoice/rhino-java?label=maven%20central%20%5Bjava%5D)](https://repo1.maven.org/maven2/ai/picovoice/rhino-java/)
[![npm](https://img.shields.io/npm/v/@picovoice/rhino-node?label=npm%20%5Bnode%5D)](https://www.npmjs.com/package/@picovoice/rhino-node)
[![npm](https://img.shields.io/npm/v/@picovoice/rhino-react?label=npm%20%5Breact%5D)](https://www.npmjs.com/package/@picovoice/rhino-react)
[![npm](https://img.shields.io/npm/v/@picovoice/rhino-react-native?label=npm%20%5Breact-native%5D)](https://www.npmjs.com/package/@picovoice/rhino-react-native)
[![npm](https://img.shields.io/npm/v/@picovoice/rhino-web?label=npm%20%5Bweb%5D)](https://www.npmjs.com/package/@picovoice/rhino-web)
[![Nuget](https://img.shields.io/nuget/v/rhino)](https://www.nuget.org/packages/Rhino/)
[![CocoaPods](https://img.shields.io/cocoapods/v/Rhino-iOS)](https://cocoapods.org/pods/Rhino-iOS)
[![Pub Version](https://img.shields.io/pub/v/rhino_flutter)](https://pub.dev/packages/rhino_flutter)
[![PyPI](https://img.shields.io/pypi/v/pvrhino)](https://pypi.org/project/pvrhino/)

Made in Vancouver, Canada by [Picovoice](https://picovoice.ai)

[![Twitter URL](https://img.shields.io/twitter/url?label=%40AiPicovoice&style=social&url=https%3A%2F%2Ftwitter.com%2FAiPicovoice)](https://twitter.com/AiPicovoice)<!-- markdown-link-check-disable-line -->
[![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCAdi9sTCXLosG1XeqDwLx7w?label=YouTube&style=social)](https://www.youtube.com/channel/UCAdi9sTCXLosG1XeqDwLx7w)

Rhino is Picovoice's Speech-to-Intent engine. It directly infers intent from spoken commands within a given context of
interest, in real-time. For example, given a spoken command:

> Can I have a small double-shot espresso?

Rhino infers what the user wants and emits the following inference result:

```json
{
  "isUnderstood": "true",
  "intent": "orderBeverage",
  "slots": {
    "beverage": "espresso",
    "size": "small",
    "numberOfShots": "2"
  }
}
```

Rhino is:

- using deep neural networks trained in real-world environments.
- compact and computationally-efficient. It is perfect for IoT.
- cross-platform:
  - Arm Cortex-M, STM32, and Arduino
  - Raspberry Pi
  - Android and iOS
  - Chrome, Safari, Firefox, and Edge
  - Linux (x86_64), macOS (x86_64, arm64), and Windows (x86_64, arm64)
- self-service. Developers can train custom contexts using [Picovoice Console](https://console.picovoice.ai/).

## Table of Contents

- [Rhino](#rhino)
  - [Table of Contents](#table-of-contents)
  - [Use Cases](#use-cases)
  - [Try It Out](#try-it-out)
  - [Language Support](#language-support)
  - [Performance](#performance)
  - [Terminology](#terminology)
  - [Demos](#demos)
    - [Python](#python-demos)
    - [.NET](#net-demos)
    - [Java](#java-demos)
    - [Unity](#unity-demos)
    - [Flutter](#flutter-demos)
    - [React Native](#react-native-demos)
    - [Android](#android-demos)
    - [iOS](#ios-demos)
    - [Web](#web-demos)
      - [Vanilla JavaScript and HTML](#vanilla-javascript-and-html)
      - [React](#react-demos)
    - [Node.js](#nodejs-demos)
    - [Rust](#rust-demos)
    - [C](#c-demos)
  - [SDKs](#sdks)
    - [Python](#python)
    - [.NET](#net)
    - [Java](#java)
    - [Unity](#unity)
    - [Flutter](#flutter)
    - [React Native](#react-native)
    - [Android](#android)
    - [iOS](#ios)
    - [Web](#web)
      - [Vanilla JavaScript and HTML (CDN Script Tag)](#vanilla-javascript-and-html-cdn-script-tag)
      - [Vanilla JavaScript and HTML (ES Modules)](#vanilla-javascript-and-html-es-modules)
      - [React](#react)
    - [Node.js](#nodejs)
    - [Rust](#rust)
    - [C](#c)
  - [Releases](#releases)
  - [FAQ](#faq)

## Use Cases

Rhino is the right choice if the domain of voice interactions is specific (limited).

- If you want to create voice experiences similar to Alexa or Google, see the [Picovoice platform](https://github.com/Picovoice/picovoice).
- If you need to recognize a few static (always listening) voice commands, see [Porcupine](https://github.com/Picovoice/porcupine).

## Try It Out

- [Interactive Web Demo](https://picovoice.ai/demos/barista/)

- Rhino and [Porcupine](https://github.com/Picovoice/porcupine) on an ARM Cortex-M7

[![Rhino in Action](https://img.youtube.com/vi/WadKhfLyqTQ/0.jpg)](https://www.youtube.com/watch?v=WadKhfLyqTQ)

## Language Support

- English, Chinese (Mandarin), French, German, Italian, Japanese, Korean, Portuguese, and Spanish.
- Support for [additional languages is available for commercial customers](https://picovoice.ai/consulting/) on a case-by-case basis.

## Performance

A comparison between the accuracy of Rhino and major cloud-based alternatives is provided
[here](https://github.com/Picovoice/speech-to-intent-benchmark). Below is the summary of the benchmark:

![](resources/.doc/benchmark.png)

## Terminology

Rhino infers the user's intent from spoken commands within a domain of interest. We refer to such a specialized domain as
a `Context`. A context can be thought of a set of voice commands, each mapped to an intent:

```yaml
turnLightOff:
  - Turn off the lights in the office
  - Turn off all lights
setLightColor:
  - Set the kitchen lights to blue
```

In examples above, each voice command is called an `Expression`. Expressions are what we expect the user to utter
to interact with our voice application.

Consider the expression:

> Turn off the lights in the office

What we require from Rhino is:

1. To infer the intent (`turnLightOff`)
2. Record the specific details from the utterance, in this case the location (`office`)

We can capture these details using slots by updating the expression:

```yaml
turnLightOff:
  - Turn off the lights in the $location:lightLocation.
```

`$location:lightLocation` means that we expect a variable of type `location` to occur, and we want to capture its value
in a variable named `lightLocation`. We call such variable a `Slot`. Slots give us the ability to capture details of the
spoken commands. Each slot type is be defined as a set of phrases. For example:

```yaml
lightLocation:
  - "attic"
  - "balcony"
  - "basement"
  - "bathroom"
  - "bedroom"
  - "entrance"
  - "kitchen"
  - "living room"
  - ...
```

You can create custom contexts using the [Picovoice Console](https://console.picovoice.ai/).

To learn the complete expression syntax of Rhino, see the [Speech-to-Intent Syntax Cheat Sheet](https://picovoice.ai/docs/tips/syntax-cheat-sheet/).

## Demos

If using SSH, clone the repository with:

```console
git clone --recurse-submodules git@github.com:Picovoice/rhino.git
```

If using HTTPS, clone the repository with:

```console
git clone --recurse-submodules https://github.com/Picovoice/rhino.git
```

### Python Demos

Install the demo package:

```console
sudo pip3 install pvrhinodemo
```

With a working microphone connected to your device run the following in the terminal:

```
rhino_demo_mic --access_key ${ACCESS_KEY} --context_path ${CONTEXT_PATH}
```

Replace `${CONTEXT_PATH}` with either a context file created using Picovoice Console or one within the repository.

For more information about Python demos, go to [demo/python](./demo/python).

### .NET Demos

[Rhino .NET demo](./demo/dotnet) is a command-line application that lets you choose between running Rhino on an audio
file or on real-time microphone input.

Make sure there is a working microphone connected to your device. From [demo/dotnet/RhinoDemo](./demo/dotnet/RhinoDemo)
run the following in the terminal:

```console
dotnet run -c MicDemo.Release -- --access_key ${ACCESS_KEY} --context_path ${CONTEXT_FILE_PATH}
```

Replace `${ACCESS_KEY}` with your Picovoice `AccessKey` and `${CONTEXT_FILE_PATH}` with either a context file created using Picovoice Console or one within the repository.

For more information about .NET demos, go to [demo/dotnet](./demo/dotnet).

### Java Demos

The [Rhino Java demo](./demo/java) is a command-line application that lets you choose between running Rhino on an
audio file or on real-time microphone input.

To try the real-time demo, make sure there is a working microphone connected to your device. Then invoke the following commands from the terminal:

```console
cd demo/java
./gradlew build
cd build/libs
java -jar rhino-mic-demo.jar -a ${ACCESS_KEY} -c ${CONTEXT_FILE_PATH}
```

Replace `${CONTEXT_FILE_PATH}` with either a context file created using Picovoice Console or one within the repository.

For more information about Java demos go to [demo/java](./demo/java).

### Unity Demos

> Unity SDKs will no longer be maintained after **December 15, 2025**. If you plan to use the Rhino Speech-to-Intent Unity SDK for commercial purposes, please [contact us](https://picovoice.ai/contact/).

To run the Rhino Unity demo, import the [Rhino Unity package](./binding/unity/rhino-3.0.1.unitypackage) into your project, open the RhinoDemo scene and hit play. To run on other platforms or in the player, go to _File > Build Settings_, choose your platform and hit the `Build and Run` button.
/
To browse the demo source go to [demo/unity](./demo/unity).

### Flutter Demos

To run the Rhino demo on Android or iOS with Flutter, you must have the [Flutter SDK](https://flutter.dev/docs/get-started/install) installed on your system. Once installed, you can run `flutter doctor` to determine any other missing requirements for your relevant platform. Once your environment has been set up, launch a simulator or connect an Android/iOS device.

Run the `prepare_demo` script with a language code to set up the demo in the language of your
choice (e.g. `de` -> German, `ko` -> Korean). To see a list of available languages, run `prepare_demo` without a language code.

```console
cd demo/flutter
dart scripts/prepare_demo.dart ${LANGUAGE}
```

Run the following command to build and deploy the demo to your device:

```console
cd demo/flutter
flutter run
```

Once the demo app has started, press the start button and utter a command to start inferring context. To see more details about the current context information, press the `Context Info` button on the top right corner in the app.

### React Native Demos

To run the React Native Rhino demo app you will first need to set up your React Native environment. For this,
please refer to [React Native's documentation](https://reactnative.dev/docs/environment-setup). Once your environment has
been set up, navigate to [demo/react-native](./demo/react-native) to run the following commands:

For Android:

```console
yarn android-install    # sets up environment
yarn android-run        # builds and deploys to Android
```

For iOS:

```console
yarn ios-install        # sets up environment
yarn ios-run            # builds and deploys to iOS
```

Both demos use a smart lighting context, which can understand commands such as:

> Turn off the lights.

or

> Set the lights in the living room to purple.

### Android Demos

Using Android Studio, open [demo/android/Activity](./demo/android/Activity) as an Android project and then run the
application.

Once the demo app has started, press the `Start` button and speak a command from the context to start inference. To see more details about
the current context information, press the `Show Context` button on the top right corner in the app.

For more information about Android demo, go to [demo/android](./demo/android).

### iOS Demos

To run the application demo:

1) From the [demo](./demo/ios) directory run:

```console
pod install
```

2) Open `RhinoDemo.xcworkspace` in XCode.

3) Replace `let accessKey = "${YOUR_ACCESS_KEY_HERE}"` in the file [ContentView.swift](./demo/ios/RhinoDemo/RhinoDemo/ContentView.swift) with your `AccessKey`.

4) Go to `Product > Scheme` and select the scheme for the language you would like to demo (e.g. `esDemo` -> Spanish Demo, `deDemo` -> German Demo)

5) Run the demo with a simulator or connected iOS device.

6) Once the demo app has started, press the `Start` button to infer audio within a context. To see more details about
the current context information, press the `Context Info` button on the top right corner in the app.

For more information about iOS demo, go to [demo/ios](./demo/ios).

### Web Demos

#### Vanilla JavaScript and HTML

From [demo/web](./demo/web) use `yarn` or `npm` to install the dependencies, and the `start` script with a language code
to start a local web server hosting the demo in the language of your choice (e.g. `pl` -> Polish, `ko` -> Korean).
To see a list of available languages, run `start` without a language code.

```console
yarn
yarn start ${LANGUAGE}
```

(or)

```console
npm install
npm run start ${LANGUAGE}
```

Open `http://localhost:5000` in your browser to try the demo.

#### React Demos

From [demo/react](./demo/react) use `yarn` or `npm` to install the dependencies, and the `start` script with a language code
to start a local web server hosting the demo in the language of your choice (e.g. `pl` -> Polish, `ko` -> Korean).
To see a list of available languages, run `start` without a language code.

```console
yarn
yarn start ${LANGUAGE}
```

(or)

```console
npm install
npm run start ${LANGUAGE}
```

Open `http://localhost:3000` in your browser to try the demo.

### Node.js Demos

Install the demo package:

```console
yarn global add @picovoice/rhino-node-demo
```

With a working microphone connected to your device, run the following in the terminal:

```console
rhn-mic-demo --access_key ${ACCESS_KEY} --context_path ${CONTEXT_FILE_PATH}
```

Replace `${CONTEXT_FILE_PATH}` with either a context file created using Picovoice Console or one within the repository.

For more information about Node.js demos go to [demo/nodejs](./demo/nodejs).

### Rust Demos

> Rust SDKs will no longer be maintained after **July 15, 2025**. If you plan to use the Rhino Speech-to-Intent Rust SDK for commercial purposes, please [contact us](https://picovoice.ai/contact/).

This demo opens an audio stream from a microphone and performs inference on spoken commands.
From [demo/rust/micdemo](./demo/rust/micdemo) run the following:

```console
cargo run --release -- --access_key ${ACCESS_KEY} --context_path ${CONTEXT_FILE_PATH}
```

Replace `${CONTEXT_FILE_PATH}` with either a context file created using Picovoice Console or one within the repository.

For more information about Rust demos go to [demo/rust](./demo/rust).

### C Demos

The C demo requires [CMake](https://cmake.org/) version 3.4 or higher.

**Windows Requires [MinGW](http://mingw-w64.org) to build the demo.**

#### Microphone Demo

At the root of the repository, build with:

```console
cmake -S demo/c/. -B demo/c/build && cmake --build demo/c/build --target rhino_demo_mic
```

##### Linux (x86_64), macOS (x86_64, arm64), and Raspberry Pi

List input audio devices with:

```console
./demo/c/build/rhino_demo_mic --show_audio_devices
```

Run the demo using:

```console
./demo/c/build/rhino_demo_mic -l ${RHINO_LIBRARY_PATH} -m lib/common/rhino_params.pv \
-c resources/contexts/${PLATFORM}/smart_lighting_${PLATFORM}.rhn \
-d ${AUDIO_DEVICE_INDEX} -a ${ACCESS_KEY}
```

Replace `${LIBRARY_PATH}` with path to appropriate library available under [lib](/lib), `${PLATFORM}` with the
name of the platform you are running on (`linux`, `raspberry-pi`, or `mac`), `${AUDIO_DEVICE_INDEX}` with
the index of your audio device and `${ACCESS_KEY}` with your Picovoice AccessKey.

##### Windows

List input audio devices with:

```console
.\\demo\\c\\build\\rhino_demo_mic.exe --show_audio_devices
```

Run the demo using:

```console
.\\demo\\c\\build\\rhino_demo_mic.exe -l lib/windows/amd64/libpv_rhino.dll -c lib/common/rhino_params.pv -c resources/contexts/windows/smart_lighting_windows.rhn -d ${AUDIO_DEVICE_INDEX} -a ${ACCESS_KEY}
```

Replace `${AUDIO_DEVICE_INDEX}` with the index of your audio device and `${ACCESS_KEY}` with your Picovoice AccessKey.

The demo opens an audio stream and infers your intent from spoken commands in the context of a smart lighting system.
For example, you can say:

> "Turn on the lights in the bedroom."

#### File Demo

At the root of the repository, build with:

```console
cmake -S demo/c/. -B demo/c/build && cmake --build demo/c/build --target rhino_demo_file
```

##### Linux (x86_64), macOS (x86_64, arm64), and Raspberry Pi

Run the demo using:

```console
./demo/c/build/rhino_demo_file -l ${LIBRARY_PATH} -m lib/common/rhino_params.pv \
-c resources/contexts/${PLATFORM}/coffee_maker_${PLATFORM}.rhn -w resources/audio_samples/test_within_context.wav \
-a ${ACCESS_KEY}
```

Replace `${LIBRARY_PATH}` with path to appropriate library available under [lib](/lib), `${PLATFORM}` with the
name of the platform you are running on (`linux`, `raspberry-pi`, or `mac`) and `${ACCESS_KEY}`
with your Picovoice AccessKey.

##### Windows

Run the demo using:

```console
.\\demo\\c\\build\\rhino_demo_file.exe -l lib/windows/amd64/libpv_rhino.dll -m lib/common/rhino_params.pv -c resources/contexts/windows/coffee_maker_windows.rhn -w resources/audio_samples/test_within_context.wav -a ${ACCESS_KEY}
```

Replace `${ACCESS_KEY}` with your Picovoice AccessKey.

The demo opens up the WAV file and infers the intent in the context of a coffee-maker system.

For more information about C demos go to [demo/c](./demo/c).

## SDKs

### Python

Install the Python SDK:

```console
pip3 install pvrhino
```

The SDK exposes a factory method to create instances of the engine:

```python
import pvrhino

access_key = "${ACCESS_KEY}" # AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

handle = pvrhino.create(access_key=access_key, context_path='/absolute/path/to/context')
```

Where `context_path` is the absolute path to the Speech-to-Intent context created either using Picovoice Console or one of
the default contexts available on Rhino's GitHub repository.

When initialized, the required sample rate can be obtained using `rhino.sample_rate`. The expected frame length
(number of audio samples in an input array) is provided by `rhino.frame_length`. The object can be used to infer intent from spoken
commands as below:

```python
def get_next_audio_frame():
    pass

while True:
    is_finalized = handle.process(get_next_audio_frame())

    if is_finalized:
        inference = handle.get_inference()
        if not inference.is_understood:
            # add code to handle unsupported commands
            pass
        else:
            intent = inference.intent
            slots = inference.slots
            # add code to take action based on inferred intent and slot values
```

Finally, when done be sure to explicitly release the resources using `handle.delete()`.

### .NET

Install the .NET SDK using NuGet or the dotnet CLI:

```console
dotnet add package Rhino
```

The SDK exposes a factory method to create instances of the engine as below:

```csharp
using Pv;

const string accessKey = "${ACCESS_KEY}";
string contextPath = "/absolute/path/to/context.rhn";
Rhino handle = Rhino.Create(accessKey, contextPath);
```

When initialized, the valid sample rate is given by `handle.SampleRate`. The expected frame length (number of audio samples
in an input array) is `handle.FrameLength`. The engine accepts 16-bit linearly-encoded PCM and operates on
single-channel audio.

```csharp
short[] GetNextAudioFrame()
{
    // .. get audioFrame
    return audioFrame;
}

while(true)
{
    bool isFinalized = handle.Process(GetNextAudioFrame());
    if(isFinalized)
    {
        Inference inference = handle.GetInference();
        if(inference.IsUnderstood)
        {
            string intent = inference.Intent;
            Dictionary<string, string> slots = inference.Slots;
            // .. code to take action based on inferred intent and slot values
        }
        else
        {
            // .. code to handle unsupported commands
        }
    }
}
```

Rhino will have its resources freed by the garbage collector, but to have resources freed
immediately after use, wrap it in a `using` statement:

```csharp
using(Rhino handle = Rhino.Create(accessKey, contextPath))
{
    // .. Rhino usage here
}
```

### Java

The Rhino Java binding is available from the Maven Central Repository at `ai.picovoice:rhino-java:${version}`.

The SDK exposes a Builder that allows you to create an instance of the engine:

```java
import ai.picovoice.rhino.*;

final String accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

try{
    Rhino handle = new Rhino.Builder()
                    .setAccessKey(accessKey)
                    .setContextPath("/absolute/path/to/context")
                    .build();
} catch (RhinoException e) { }
```

When initialized, the valid sample rate is given by `handle.getSampleRate()`. The expected frame length (number of audio samples
in an input array) is `handle.getFrameLength()`. The engine accepts 16-bit linearly-encoded PCM and operates on
single-channel audio.

```java
short[] getNextAudioFrame(){
    // .. get audioFrame
    return audioFrame;
}

while(true) {
    boolean isFinalized = handle.process(getNextAudioFrame());
    if(isFinalized){
        RhinoInference inference = handle.getInference();
        if(inference.getIsUnderstood()){
            String intent = inference.getIntent();
            Map<string, string> slots = inference.getSlots();
            // .. code to take action based on inferred intent and slot values
        } else {
            // .. code to handle unsupported commands
        }
    }
}
```

Once you are done with Rhino, ensure you release its resources explicitly:

```java
handle.delete();
```

### Unity

> Unity SDKs will no longer be maintained after **December 15, 2025**. If you plan to use the Rhino Speech-to-Intent Unity SDK for commercial purposes, please [contact us](https://picovoice.ai/contact/).

Import the [Rhino Unity Package](./binding/unity/rhino-3.0.1.unitypackage) into your Unity project.

The SDK provides two APIs:

#### High-Level API

[RhinoManager](./binding/unity/Assets/Rhino/RhinoManager.cs) provides a high-level API that takes care of audio recording. This class is the quickest way to get started.

Using the constructor `RhinoManager.Create` will create an instance of the RhinoManager using the provided context file.

```csharp
using Pv.Unity;

string accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

try
{
    RhinoManager _rhinoManager = RhinoManager.Create(
                                    accessKey,
                                    "/path/to/context/file.rhn",
                                    (inference) => {});
}
catch (Exception ex)
{
    // handle rhino init error
}
```

Once you have instantiated a RhinoManager, you can start audio capture and intent inference by calling:

```csharp
_rhinoManager.Process();
```

Audio capture stops and Rhino resets once an inference result is returned via the inference callback. When you wish to result, call `.Process()` again.

Once the app is done with using an instance of RhinoManager, you can explicitly release the audio resources, and the resources allocated to Rhino:

```csharp
_rhinoManager.Delete();
```

There is no need to deal with audio capture to enable intent inference with RhinoManager.
This is because it uses our
[unity-voice-processor](https://github.com/Picovoice/unity-voice-processor/)
Unity package to capture frames of audio and automatically pass it to the inference engine.

#### Low-Level API

[Rhino](./binding/unity/Assets/Rhino/Rhino.cs) provides low-level access to the inference engine for those who want to incorporate speech-to-intent into an already existing audio processing pipeline.

To create an instance of `Rhino`, use the `.Create` static constructor, and a context file.

```csharp
using Pv.Unity;

string accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

try
{
    Rhino _rhino = Rhino.Create(accessKey, "path/to/context/file.rhn");
}
catch (RhinoException ex)
{
    // handle rhino init error
}
```

To feed Rhino your audio, you must send it frames of audio to its `Process` function until it has made an inference.

```csharp
short[] GetNextAudioFrame()
{
    // .. get audioFrame
    return audioFrame;
}

try
{
    bool isFinalized = _rhino.Process(GetNextAudioFrame());
    if(isFinalized)
    {
        Inference inference = _rhino.GetInference();
        if(inference.IsUnderstood)
        {
            string intent = inference.Intent;
            Dictionary<string, string> slots = inference.Slots;
            // .. code to take action based on inferred intent and slot values
        }
        else
        {
            // .. code to handle unsupported commands
        }
    }
}
catch (RhinoException ex)
{
    Debug.LogError(ex.ToString());
}
```

For process to work correctly, the audio data must be in the audio format required by Picovoice.

Rhino implements the `IDisposable` interface, so you can use Rhino in a `using` block. If you don't use a `using` block, resources will be released by the garbage collector automatically, or you can explicitly release the resources like so:

```csharp
_rhino.Dispose();
```

### Flutter

Add the [Rhino Flutter plugin](https://pub.dev/packages/rhino) to your pub.yaml.

```yaml
dependencies:
  rhino_flutter: ^<version>
```

The SDK provides two APIs:

#### High-Level API

[RhinoManager](./binding/flutter/lib/rhino_manager.dart) provides a high-level API that takes care of audio recording. This class is the quickest way to get started.

The constructor `RhinoManager.create` will create an instance of the RhinoManager using a context file that you pass to it.

```dart
import 'package:rhino_flutter/rhino_manager.dart';
import 'package:rhino_flutter/rhino_error.dart';

final String accessKey = "{ACCESS_KEY}";  // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

void createRhinoManager() async {
    try{
        _rhinoManager = await RhinoManager.create(
            accessKey,
            "/path/to/context/file.rhn",
            _inferenceCallback);
    } on RhinoException catch (err) {
        // handle rhino init error
    }
}
```

The `inferenceCallback` parameter is a function that you want to execute when Rhino makes an inference.
The function should accept a `RhinoInference` instance that represents the inference result.

```dart
void _inference(RhinoInference inference) {
    if(inference.isUnderstood!) {
        String intent = inference.intent!;
        Map<String, String> = inference.slots!;
        // add code to take action based on inferred intent and slot values
    }
    else {
        // add code to handle unsupported commands
    }
}
```

Once you have instantiated a RhinoManager, you can start audio capture and intent inference using the `.process()` function.
Audio capture stops and rhino resets once an inference result is returned via the inference callback.

```dart
try {
    await _rhinoManager.process();
} on RhinoException catch (ex) { }
```

Once your app is done with using RhinoManager, be sure you explicitly release the resources allocated for it:

```dart
_rhinoManager.delete();
```

Our [flutter_voice_processor](https://github.com/Picovoice/flutter-voice-processor/) Flutter plugin captures the frames of audio and automatically passes it to the speech-to-intent engine.

#### Low-Level API

[Rhino](./binding/flutter/lib/rhino.dart) provides low-level access to the inference engine for those who want to incorporate
speech-to-intent into an already existing audio processing pipeline.

`Rhino` is created by passing a context file to its static constructor `create`:

```dart
import 'package:rhino_flutter/rhino_manager.dart';
import 'package:rhino_flutter/rhino_error.dart';

final String accessKey = "{ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

void createRhino() async {
    try {
        _rhino = await Rhino.create(accessKey, '/path/to/context/file.rhn');
    } on RhinoException catch (err) {
        // handle rhino init error
    }
}
```

To deliver audio to the engine, you must send audio frames to its `process` function.
Each call to `process` will return a `RhinoInference` instance with following variables:

- isFinalized - true if Rhino has made an inference, false otherwise
- isUnderstood - **null** if `isFinalized` is false, otherwise true if Rhino understood what it heard based on the context or false if it did not
- intent - **null** if `isUnderstood` is not true, otherwise name of intent that were inferred
- slots - **null** if `isUnderstood` is not true, otherwise the dictionary of slot keys and values that were inferred

```dart
List<int> buffer = getAudioFrame();

try {
    RhinoInference inference = await _rhino.process(buffer);
    if(inference.isFinalized) {
        if(inference.isUnderstood!) {
            String intent = inference.intent!;
            Map<String, String> = inference.slots!;
            // add code to take action based on inferred intent and slot values
        }
    }
} on RhinoException catch (error) {
    // handle error
}

// once you are done
this._rhino.delete();
```

### React Native

Install [@picovoice/react-native-voice-processor](https://www.npmjs.com/package/@picovoice/react-native-voice-processor) and
[@picovoice/rhino-react-native](https://www.npmjs.com/package/@picovoice/rhino-react-native). The SDK provides two APIs:

#### High-Level API

[RhinoManager](./binding/react-native/src/rhino_manager.tsx) provides a high-level API that takes care of
audio recording. This class is the quickest way to get started.

The constructor `RhinoManager.create` will create an instance of a RhinoManager using a context file that you pass to it.

```javascript
const accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

async createRhinoManager(){
    try{
        this._rhinoManager = await RhinoManager.create(
            accessKey,
            '/path/to/context/file.rhn',
            inferenceCallback);
    } catch (err) {
        // handle error
    }
}
```

Once you have instantiated a RhinoManager, you can start/stop audio capture and intent inference by calling `.process()`.
Upon receiving an inference callback, audio capture will stop automatically and Rhino will reset. To restart it you must
call `.process()` again.

```javascript
let didStart = await this._rhinoManager.process();
```

When you are done using Rhino, you must explicitly release resources:

```javascript
this._rhinoManager.delete();
```

[@picovoice/react-native-voice-processor](https://github.com/Picovoice/react-native-voice-processor/) handles
audio capture and RhinoManager passes frames to the inference engine for you.

#### Low-Level API

[Rhino](./binding/react-native/src/rhino.tsx) provides low-level access to the inference engine for those
who want to incorporate speech-to-intent into an already existing audio processing pipeline.

`Rhino` is created by passing a context file to its static constructor `create`:

```javascript
const accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

async createRhino(){
    try{
        this._rhino = await Rhino.create(accessKey, '/path/to/context/file.rhn');
    } catch (err) {
        // handle error
    }
}
```

To deliver audio to the engine, you must pass it audio frames
using the `process` function. The `RhinoInference` result that is returned from `process` will have up to four fields:

- isFinalized - true if Rhino has made an inference, false otherwise
- isUnderstood - **null** if `isFinalized` is false, otherwise true if Rhino understood what it heard based on the context or false if it did not
- intent - **null** if `isUnderstood` is not true, otherwise name of intent that were inferred
- slots - **null** if `isUnderstood` is not true, otherwise the dictionary of slot keys and values that were inferred

```javascript
let buffer = getAudioFrame();
try {
    let inference = await this._rhino.process(buffer);
    // use result
    // ..
    }
} catch (e) {
    // handle error
}

// once you are done
this._rhino.delete();
```

### Android

To include the package in your Android project, ensure you have included `mavenCentral()` in your top-level `build.gradle` file and then add the following to your app's `build.gradle`:

```groovy
dependencies {
    implementation 'ai.picovoice:rhino-android:${LATEST_VERSION}'
}
```

There are two possibilities for integrating Rhino into an Android application: the High-level API and the Low-level API.

#### High-Level API

[RhinoManager](binding/android/Rhino/rhino/src/main/java/ai/picovoice/rhino/RhinoManager.java) provides a high-level API
for integrating Rhino into Android applications. It manages all activities related to creating an input audio stream,
feeding it into Rhino, and invoking a user-provided inference callback. Context files (`.rhn`)
should be placed under the Android project assets folder (`src/main/assets/`).

```java
final String accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)
final String contextPath = "/path/to/context.rhn" // path relative to 'assets' folder

try {
    RhinoManager rhinoManager = new RhinoManager.Builder()
                        .setAccessKey(accessKey)
                        .setContextPath("/path/to/context.rhn")
                        .setSensitivity(0.35f)
                        .build(appContext, new RhinoManagerCallback() {
                            @Override
                            public void invoke(RhinoInference inference) {
                                if (inference.getIsUnderstood()) {
                                    final String intent = inference.getIntent();
                                    final Map<String, String> slots = inference.getSlots();
                                    // add code to take action based on inferred intent and slot values
                                }
                                else {
                                    // add code to handle unsupported commands
                                }
                            }
                        });
} catch (RhinoException e) { }
```

The `appContext` parameter is the Android application context - this is used to extract Rhino resources from the APK.
Sensitivity is the parameter that enables developers to trade miss rate for false alarm. It is a floating-point number within
[0, 1]. A higher sensitivity reduces miss rate at cost of increased false alarm rate.

When initialized, input audio can be processed using `manager.process()`. When done, be sure to release the resources
using `manager.delete()`.

#### Low-Level API

Rhino provides a binding for Android using JNI. It can be initialized using:

```java
import ai.picovoice.rhino.*;

final String accessKey = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

try {
    Rhino rhino = new Rhino.Builder()
                        .setAccessKey(accessKey)
                        .setContextPath("/path/to/context.rhn")
                        .build(appContext);
} catch (RhinoException e) { }
```

Once initialized, `handle` can be used for intent inference:

```java
private short[] getNextAudioFrame();

while (!handle.process(getNextAudioFrame()));

final RhinoInference inference = handle.getInference();
if (inference.getIsUnderstood()) {
    // logic to perform an action given the intent object.
} else {
    // logic for handling out of context or unrecognized command
}
```

Finally, prior to exiting the application be sure to release resources acquired:

```java
handle.delete()
```

### iOS

<!-- markdown-link-check-disable -->
The Rhino iOS binding is available via [CocoaPods](https://cocoapods.org/pods/Rhino-iOS). To import it into your iOS project, add the following line to your Podfile and run `pod install`:
<!-- markdown-link-check-enable -->

```ruby
pod 'Rhino-iOS'
```

There are two approaches for integrating Rhino into an iOS application: The high-level API and the low-level API.

#### High-Level API

[RhinoManager](./binding/ios/RhinoManager.swift) provides a high-level API
for integrating Rhino into iOS applications. It manages all activities related to creating an input audio stream, feeding it to the engine, and invoking a user-provided inference callback.
```swift
import Rhino

let accessKey = "${ACCESS_KEY}" // Obtained from Picovoice Console (https://console.picovoice.ai)
do {
    let manager = try RhinoManager(
        accessKey: accessKey,
        contextPath: "/path/to/context/file.rhn",
        modelPath: "/path/to/model/file.pv",
        sensitivity: 0.35,
        onInferenceCallback: { inference in
                if inference.isUnderstood {
                    let intent:String = inference.intent
                    let slots:Dictionary<String,String> = inference.slots
                    // use inference results
                }
            })
} catch { }
```

Sensitivity is the parameter that enables developers to trade miss rate for false alarm. It is a floating-point number within
[0, 1]. A higher sensitivity reduces miss rate at cost of increased false alarm rate.

When initialized, input audio can be processed using `manager.process()`. When done, be sure to release the resources
using `manager.delete()`.

#### Low-Level API

[Rhino](./binding/ios/Rhino.swift) provides low-level access to the Speech-to-Intent engine for those who want to incorporate intent inference into an already existing audio processing pipeline.

```swift
import Rhino

let accessKey = "${ACCESS_KEY}" // Obtained from Picovoice Console (https://console.picovoice.ai)
do {
    let handle = try Rhino(
      accessKey: accessKey,
      contextPath: "/path/to/context/file.rhn")
} catch { }
```

Once initialized, `handle` can be used for intent inference:

```swift
func getNextAudioFrame() -> [Int16] {
    // .. get audioFrame
    return audioFrame
}

while true {
    do {
        let isFinalized = try handle.process(getNextAudioFrame())
        if isFinalized {
            let inference = try handle.getInference()
            if inference.isUnderstood {
                let intent:String = inference.intent
                let slots:Dictionary<String, String> = inference.slots
                // add code to take action based on inferred intent and slot values
            }
        }
    } catch { }
}
```

Finally, prior to exiting the application be sure to release resources acquired:

```swift
handle.delete()
```

### Web

Rhino is available on modern web browsers (i.e. not Internet Explorer) via [WebAssembly](https://webassembly.org/). Microphone audio is handled via the [Web Audio API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API) and is abstracted by the WebVoiceProcessor, which also handles downsampling to the correct format. Rhino is provided pre-packaged as a [Web Worker](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API/Using_web_workers).

#### Vanilla JavaScript and HTML (CDN Script Tag)

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <script src="https://unpkg.com/@picovoice/rhino-web/dist/iife/index.js"></script>
    <script src="https://unpkg.com/@picovoice/web-voice-processor/dist/iife/index.js"></script>
    <script type="application/javascript">
      const RHINO_CONTEXT_BASE64 = /* Base64 representation of `.rhn` context file  */;
      const RHINO_MODEL_BASE64 = /* Base64 representation of the `.pv` model file */;

      let rhino = null;

      function rhinoInferenceCallback(inference) {
        if (inference.isFinalized) {
          console.log(`Inference detected: ${JSON.stringify(inference)}`);
          WebVoiceProcessor.WebVoiceProcessor.unsubscribe(rhino);
          document.getElementById("push-to-talk").disabled = false;
          console.log("Press the 'Push to Talk' button to speak again.");
        }
      }

      async function startRhino() {
        console.log("Rhino is loading. Please wait...");
        rhino = await RhinoWeb.RhinoWorker.create(
            accessKey: "${ACCESS_KEY}",  // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)
            { base64: RHINO_CONTEXT_BASE64 },
            rhinoInferenceCallback,
            { base64: RHINO_MODEL_BASE64 }
        );

        console.log("Rhino worker ready!");
        document.getElementById("push-to-talk").disabled = false;
        writeMessage("Press the 'Push to Talk' button to talk.");
      }

      document.addEventListener("DOMContentLoaded", function () {
        document.getElementById("push-to-talk").onclick = function (event) {
          if (rhino) {
            console.log("Rhino is listening for your commands ...");
            this.disabled = true;
            WebVoiceProcessor.WebVoiceProcessor.subscribe(rhino);
          }
        };
      });
    </script>
  </head>
  <body>
    <button id="push-to-talk">Push to Talk</button>
  </body>
</html>

```

#### Vanilla JavaScript and HTML (ES Modules)

```console
yarn add @picovoice/rhino-web @picovoice/web-voice-processor
```

(or)

```console
npm install @picovoice/rhino-web @picovoice/web-voice-processor
```

```javascript
import { WebVoiceProcessor } from "@picovoice/web-voice-processor"
import { RhinoWorker } from "@picovoice/rhino-web";

const RHN_CONTEXT_BASE64 = /* Base64 representation of a `.rhn` context file */
const RHINO_MODEL_BASE64 = /* Base64 representation of the `.pv` model file*/;

let rhino = null

function rhinoInferenceCallback(inference) {
  if (inference.isFinalized) {
    console.log(`Rhino inference: ${JSON.stringify(inference)}`);
    WebVoiceProcessor.unsubscribe(rhino);
  }
}

async function startRhino() {
  // Create a Rhino Worker to listen for commands in the specified context
  rhino = await RhinoWorker.create(
    accessKey: "${ACCESS_KEY}",  // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)
    { base64: RHINO_CONTEXT_BASE64 },
    rhinoInferenceCallback,
    { base64: RHINO_MODEL_BASE64 }
  );
}

// Start a voice interaction:
// WebVoiceProcessor will request microphone permission.
// n.b. This promise will reject if the user refuses permission! Make sure you handle that possibility.
function pushToTalk() {
  if (rhino) {
    WebVoiceProcessor.subscribe(rhino);
  }
}

startRhino()

...

// Finished with Rhino? Release the WebVoiceProcessor and the worker.
if (done) {
  WebVoiceProcessor.unsubscribe(rhino);
  rhino.release()
  rhino.terminate()
}
```

#### React

```console
yarn add @picovoice/rhino-react @picovoice/web-voice-processor
```

(or)

```console
npm install @picovoice/rhino-react @picovoice/web-voice-processor
```

```javascript
import React, { useEffect } from 'react';
import { useRhino } from '@picovoice/rhino-react';

const RHINO_CONTEXT_BASE64 = /* Base64 representation of a Rhino context (.rhn) for WASM, omitted for brevity */
const RHN_MODEL_BASE64 = /* Base64 representation of a Rhino parameter model (.pv), omitted for brevity */

function VoiceWidget(props) {
  const {
    inference,
    contextInfo,
    isLoaded,
    isListening,
    error,
    init,
    process,
    release,
  } = useRhino();

  useEffect(() => {
    if (!isLoaded) {
      init(
        "${ACCESS_KEY}", // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)
        { base64: RHINO_CONTEXT_BASE64 },
        { base64: RHN_MODEL_BASE64 }
      );
    }
  }, [isLoaded])

return (
  <div className="voice-widget">
    <button onClick={() => process()} disabled={isListening || !isLoaded || error !== null}>
      Process
    </button>
    <p>{JSON.stringify(inference)}</p>
  </div>
)
```

### Node.js

Install the Node.js SDK:

```console
yarn add @picovoice/rhino-node
```

Create instances of the Rhino class by specifying the path to the context file:

```javascript
const Rhino = require("@picovoice/rhino-node");
const accessKey = "${ACCESS_KEY}" // Obtained from the Picovoice Console (https://console.picovoice.ai/)
let handle = new Rhino(accessKey, "/path/to/context/file.rhn");
```

When instantiated, `handle` can process audio via its `.process` method:

```javascript
let getNextAudioFrame = function() {
    ...
};

let isFinalized = false;
while (!isFinalized) {
  isFinalized = handle.process(getNextAudioFrame());
  if (isFinalized) {
    let inference = engineInstance.getInference();
    // Insert inference event callback
  }
}
```

When done, be sure to release resources acquired by WebAssembly using `release()`:

```javascript
handle.release();
```

### Rust

> Rust SDKs will no longer be maintained after **July 15, 2025**. If you plan to use the Rhino Speech-to-Intent Rust SDK for commercial purposes, please [contact us](https://picovoice.ai/contact/).

First you will need [Rust and Cargo](https://rustup.rs/) installed on your system.

To add the rhino library into your app, add `pv_rhino` to your apps `Cargo.toml` manifest:
```toml
[dependencies]
pv_rhino = "*"
```

To create an instance of the engine you first create a `RhinoBuilder` instance with the configuration parameters for the speech to intent engine and then make a call to `.init()`:

```rust
use rhino::RhinoBuilder;

let access_key = "${ACCESS_KEY}"; // AccessKey obtained from Picovoice Console (https://console.picovoice.ai/)

let rhino: Rhino = RhinoBuilder::new(access_key, "/path/to/context/file.rhn").init().expect("Unable to create Rhino");
```

To feed audio into Rhino, use the `process` function in your capture loop:
```rust
fn next_audio_frame() -> Vec<i16> {
    // get audio frame
}

loop {
    if let Ok(is_finalized) = rhino.process(&next_audio_frame()) {
        if is_finalized {
            if let Ok(inference) = rhino.get_inference() {
                if inference.is_understood {
                    let intent = inference.intent.unwrap();
                    let slots = inference.slots;
                    // add code to take action based on inferred intent and slot values
                } else {
                    // add code to handle unsupported commands
                }
            }
        }
    }
}
```

### C

Rhino is implemented in ANSI C and therefore can be directly linked to C applications. The [pv_rhino.h](./include/pv_rhino.h)
header file contains relevant information. An instance of the Rhino object can be constructed as follows:

```c
const char *access_key = "${ACCESS_KEY}" // obtained from the Picovoice Console (https://console.picovoice.ai/)
const char *model_path = ... // Available at lib/common/rhino_params.pv
const char *context_path = ... // absolute path to context file for the domain of interest
const float sensitivity = 0.5f;
bool require_endpoint = false;

pv_rhino_t *handle = NULL;
const pv_status_t status = pv_rhino_init(access_key, model_path, context_path, sensitivity, require_endpoint, &handle);
if (status != PV_STATUS_SUCCESS) {
    // add error handling code
}
```

Now the `handle` can be used to infer intent from an incoming audio stream. Rhino accepts single channel, 16-bit PCM
audio. The sample rate can be retrieved using `pv_sample_rate()`. Finally, Rhino accepts input audio in consecutive chunks
(frames); the length of each frame can be retrieved using `pv_rhino_frame_length()`.

```c
extern const int16_t *get_next_audio_frame(void);

while (true) {
    const int16_t *pcm = get_next_audio_frame();

    bool is_finalized = false;
    pv_status_t status = pv_rhino_process(handle, pcm, &is_finalized);
    if (status != PV_STATUS_SUCCESS) {
        // add error handling code
    }

    if (is_finalized) {
        bool is_understood = false;
        status = pv_rhino_is_understood(rhino, &is_understood);
        if (status != PV_STATUS_SUCCESS) {
            // add error handling code
        }

        if (is_understood) {
            const char *intent = NULL;
            int32_t num_slots = 0;
            const char **slots = NULL;
            const char **values = NULL;
            status = pv_rhino_get_intent(rhino, &intent, &num_slots, &slots, &values);
            if (status != PV_STATUS_SUCCESS) {
                // add error handling code
            }

            // add code to take action based on inferred intent and slot values

            pv_rhino_free_slots_and_values(rhino, slots, values);
        } else {
            // add code to handle unsupported commands
        }

        pv_rhino_reset(rhino);
    }
}
```

When done, remember to release the resources acquired.

```c
pv_rhino_delete(rhino);
```

## Releases

### v3.0.0 - October 26th, 2023

- Improvements to error reporting
- Upgrades to authorization and authentication system
- Added `reset()` function to API
- Various bug fixes and improvements
- Node min support bumped to 16
- Unity editor min support bumped to 2021
- Patches to .NET support

### v2.2.0 - April 12th, 2023

- Added language support for Arabic, Dutch, Hindi, Mandarin, Polish, Russian, Swedish and Vietnamese
- Added support for .NET 7.0 and fixed support for .NET Standard 2.0
- iOS minimum support moved to 11.0
- Improved stability and performance

### v2.1.0 - January 20th, 2022

- Added macOS arm64 support for Java and Unity SDKs
- Support added for non-English built-in slots
- Support for Macros added
- Various bug fixes and improvements

### v2.0.0 - November 25th, 2021

- Improved accuracy
- Added Rust SDK
- macOS arm64 support
- Added NodeJS support for Windows, NVIDIA Jetson Nano, and BeagleBone
- Added .NET support for NVIDIA Jetson Nano and BeagleBone
- Runtime optimization

### v1.6.0 - December 2nd, 2020

- Added support for React Native
- Added support for Java
- Added support for .NET
- Added support for NodeJS

### v1.5.0 - June 4th, 2020

- Accuracy improvements

### v1.4.0 - April 13th, 2020

- Accuracy improvements
- Builtin slots

### v1.3.0 - February 13th, 2020

- Accuracy improvements
- Runtime optimizations
- Added support for Raspberry Pi 4
- Added support for JavaScript
- Added support for iOS
- Updated documentation

### v1.2.0 - April 26, 2019

- Accuracy improvements
- Runtime optimizations

### v1.1.0 - December 23rd, 2018

- Accuracy improvements
- Open-sourced Raspberry Pi build

### v1.0.0 - November 2nd, 2018

- Initial Release

## FAQ

You can find the FAQ [here](https://picovoice.ai/docs/faq/rhino/).
