plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}
android {
    namespace = "com.arcadelab.spinwin"
    compileSdk = 35
    defaultConfig {
        applicationId = "com.arcadelab.spinwin"
        minSdk = 23
        targetSdk = 35
        versionCode = 1
        versionName = "0.1.0"
        externalNativeBuild { cmake { cppFlags += "-std=c++17" } }
        ndk { abiFilters += listOf("arm64-v8a", "armeabi-v7a") }
    }
    externalNativeBuild { cmake { path = file("src/main/cpp/CMakeLists.txt") } }
}
dependencies {
    implementation("androidx.activity:activity-ktx:1.10.1")
    implementation("androidx.documentfile:documentfile:1.0.1")
}
