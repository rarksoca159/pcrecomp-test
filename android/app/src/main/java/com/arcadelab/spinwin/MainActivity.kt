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
    private lateinit var exportSaveButton: Button
    private val gameDir by lazy { File(filesDir, "spinwin") }
    private val saveFile by lazy { File(gameDir, "settings.bin") }

    private external fun nativeEngineStatus(): String

    private val folderPicker = registerForActivityResult(ActivityResultContracts.OpenDocumentTree()) { uri: Uri? ->
        if (uri != null) {
            try {
                contentResolver.takePersistableUriPermission(uri, Intent.FLAG_GRANT_READ_URI_PERMISSION)
                val selected = DocumentFile.fromTreeUri(this, uri) ?: error("Cannot read selected folder")
                copyTree(selected, gameDir)
                val valid = File(gameDir, "SpinWin.exe").exists() &&
                    File(gameDir, "Graphics").isDirectory && File(gameDir, "Audio").isDirectory
                status.text = if (valid) {
                    "${nativeEngineStatus()}\nGame files imported. Try the SDL2 graphics test below."
                } else {
                    "Some expected files are missing. Select the main 'Spin & Win' folder."
                }
                playButton.isEnabled = valid
            } catch (e: Exception) {
                status.text = "Import failed: ${e.message ?: "unknown error"}"
            }
        }
    }

    private val importSavePicker = registerForActivityResult(ActivityResultContracts.OpenDocument()) { uri: Uri? ->
        if (uri != null) {
            try {
                if (!gameDir.exists() && !gameDir.mkdirs()) error("Cannot create game folder")
                contentResolver.openInputStream(uri)?.use { input ->
                    FileOutputStream(saveFile).use { output -> input.copyTo(output) }
                } ?: error("Cannot read selected save file")
                status.text = "Save file imported as settings.bin. You can now play."
                refreshSaveButton()
            } catch (e: Exception) {
                status.text = "Save import failed: ${e.message ?: "unknown error"}"
            }
        }
    }

    private val exportSavePicker = registerForActivityResult(ActivityResultContracts.CreateDocument("application/octet-stream")) { uri: Uri? ->
        if (uri != null) {
            try {
                if (!saveFile.isFile) error("settings.bin was not found. Play the game and return here first.")
                contentResolver.openOutputStream(uri, "wt")?.use { output ->
                    saveFile.inputStream().use { input -> input.copyTo(output) }
                } ?: error("Cannot write selected destination")
                status.text = "settings.bin exported. Keep this file before uninstalling the app."
            } catch (e: Exception) {
                status.text = "Save export failed: ${e.message ?: "unknown error"}"
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        System.loadLibrary("spinwin_android")
        buildScreen()
        refreshStatus()
    }

    override fun onResume() {
        super.onResume()
        if (::status.isInitialized && ::playButton.isInitialized) refreshStatus()
    }

    private fun refreshSaveButton() {
        if (::exportSaveButton.isInitialized) exportSaveButton.isEnabled = saveFile.isFile
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
            setPadding(0, 8, 0, 20)
        })
        layout.addView(Button(this).apply {
            text = "SELECT GAME FOLDER"
            setOnClickListener { folderPicker.launch(null) }
        })
        layout.addView(Button(this).apply {
            text = "IMPORT SAVE FILE (settings.bin)"
            setOnClickListener { importSavePicker.launch(arrayOf("*/*")) }
        })
        exportSaveButton = Button(this).apply {
            text = "EXPORT SAVE FILE (settings.bin)"
            isEnabled = saveFile.isFile
            setOnClickListener {
                if (saveFile.isFile) exportSavePicker.launch("settings.bin")
                else Toast.makeText(this@MainActivity, "Play the game and return here first.", Toast.LENGTH_LONG).show()
            }
        }
        layout.addView(exportSaveButton)
        layout.addView(Button(this).apply {
            text = "TEST SDL2 GRAPHICS + TOUCH"
            setOnClickListener {
                startActivity(Intent(this@MainActivity, SDLGameActivity::class.java))
            }
        })
        playButton = Button(this).apply {
            text = "PLAY SPIN & WIN"; isEnabled = false
            setOnClickListener {
                startActivity(Intent(this@MainActivity, SDLGameActivity::class.java))
            }
        }
        layout.addView(playButton)
        status = TextView(this).apply {
            textSize = 14f; setTextColor(0xFFFFE0E0.toInt())
            gravity = Gravity.CENTER; setPadding(0, 18, 0, 0)
        }
        layout.addView(status)
        setContentView(layout)
    }

    private fun refreshStatus() {
        val runtime = nativeEngineStatus()
        val valid = File(gameDir, "SpinWin.exe").exists() &&
            File(gameDir, "Graphics").isDirectory && File(gameDir, "Audio").isDirectory
        playButton.isEnabled = valid
        refreshSaveButton()
        status.text = if (valid)
            "$runtime\nGame files are ready. Tap PLAY SPIN & WIN."
        else "$runtime\nChoose the extracted 'Spin & Win' game folder to import its files."
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
