package com.arcadelab.spinwin

import androidx.activity.ComponentActivity
import android.os.Bundle
import android.content.Intent
import android.net.Uri
import android.view.Gravity
import android.widget.Button
import android.widget.LinearLayout
import android.widget.TextView
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.documentfile.provider.DocumentFile
import java.io.File
import java.io.FileOutputStream

class MainActivity : ComponentActivity() {
    private lateinit var status: TextView
    private lateinit var playButton: Button
    private val gameDir by lazy { File(filesDir, "spinwin") }

    private val folderPicker = registerForActivityResult(ActivityResultContracts.OpenDocumentTree()) { uri: Uri? ->
        if (uri != null) {
            try {
                contentResolver.takePersistableUriPermission(uri, Intent.FLAG_GRANT_READ_URI_PERMISSION)
                val selected = DocumentFile.fromTreeUri(this, uri) ?: error("Cannot read selected folder")
                copyTree(selected, gameDir)
                val valid = File(gameDir, "SpinWin.exe").exists() &&
                    File(gameDir, "Graphics").isDirectory && File(gameDir, "Audio").isDirectory
                status.text = if (valid) {
                    "Game files imported. The Android engine is still being ported."
                } else {
                    "Some expected files are missing. Select the main 'Spin & Win' folder."
                }
                playButton.isEnabled = false
            } catch (e: Exception) {
                status.text = "Import failed: ${e.message ?: "unknown error"}"
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        System.loadLibrary("spinwin_android")
        buildScreen()
        refreshStatus()
    }

    private fun buildScreen() {
        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            gravity = Gravity.CENTER
            setPadding(28, 24, 28, 24)
            setBackgroundColor(0xFF601010.toInt())
        }
        layout.addView(TextView(this).apply {
            text = "SPIN & WIN"; textSize = 34f
            setTextColor(0xFFFFE0E0.toInt()); gravity = Gravity.CENTER
        })
        layout.addView(TextView(this).apply {
            text = "Arcade Lab • Android port"; textSize = 16f
            setTextColor(0xFFFFC8C8.toInt()); gravity = Gravity.CENTER
            setPadding(0, 8, 0, 24)
        })
        layout.addView(Button(this).apply {
            text = "SELECT GAME FOLDER"
            setOnClickListener { folderPicker.launch(null) }
        })
        playButton = Button(this).apply {
            text = "PLAY"; isEnabled = false
            setOnClickListener {
                Toast.makeText(this@MainActivity, "The game engine is not integrated yet.", Toast.LENGTH_LONG).show()
            }
        }
        layout.addView(playButton)
        status = TextView(this).apply {
            textSize = 14f; setTextColor(0xFFFFE0E0.toInt())
            gravity = Gravity.CENTER; setPadding(0, 20, 0, 0)
        }
        layout.addView(status)
        setContentView(layout)
    }

    private fun refreshStatus() {
        status.text = if (File(gameDir, "SpinWin.exe").exists())
            "Game files are present. Engine port is in progress; Play is disabled."
        else "Choose the extracted 'Spin & Win' game folder to import its files."
    }

    private fun copyTree(source: DocumentFile, destination: File) {
        if (!destination.exists() && !destination.mkdirs()) error("Cannot create app storage folder")
        for (child in source.listFiles()) {
            val target = File(destination, child.name ?: continue)
            if (child.isDirectory) copyTree(child, target)
            else if (child.isFile) {
                contentResolver.openInputStream(child.uri)?.use { input ->
                    FileOutputStream(target).use { output -> input.copyTo(output) }
                } ?: error("Cannot read ${child.name}")
            }
        }
    }
}
