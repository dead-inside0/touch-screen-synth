
package com.ernestlevkovich.touchsynth

import android.media.MediaDrm.LogMessage
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.gestures.detectDragGestures
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.input.pointer.PointerInputChange
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.platform.LocalConfiguration

var xPosition = 0.0f;
var yPosition = 0.0f;

val minFreq = 220.0f;
val maxFreq = 440.0f;

val minAmp = -20f;

class MainActivity : ComponentActivity() {
    companion object {
        init {
            System.loadLibrary("touchsynth")
        }
    }
    private external fun initAudio();
    private external fun closeAudio();
    private external fun changeFrequency(f : Float);
    private external fun changeAmplitude(a : Float);
    external fun playSynth();
    external fun pauseSynth();
    init {
        initAudio();
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            TouchSurface(xPosFun = {f -> changeAmplitude(f)}, yPosFun = {a -> changeFrequency(a)}, playFun = {playSynth()},pauseFun = {pauseSynth()})
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        closeAudio();
    }
}

@Composable
fun TouchSurface(modifier: Modifier = Modifier,
                 xPosFun : (Float) -> Unit,
                 yPosFun : (Float) -> Unit,
                 playFun : () -> Unit,
                 pauseFun : () -> Unit){
    val configuration = LocalConfiguration.current
    val screenWidth = configuration.screenWidthDp
    val screenHeight = configuration.screenHeightDp
    var touchPosition by remember { mutableStateOf(Offset.Zero) }
    var touchActive by remember { mutableStateOf(false) }
    Canvas(
        modifier = modifier
            .fillMaxSize()
            .pointerInput(key1 = Unit) {
                detectDragGestures(
                    onDragStart = { offset: Offset ->
                        touchActive = true;
                        playFun();
                        xPosition = offset.x
                        yPosition = offset.y
                        touchPosition = offset
                        val frequency = (yPosition * (maxFreq - minFreq))/screenHeight;
                        val amplitude = (1-xPosition) / screenWidth;
                        yPosFun(frequency);
                        xPosFun(amplitude)
                    },
                    onDrag = { change: PointerInputChange, _: Offset ->
                        touchActive = true;
                        playFun();
                        xPosition = change.position.x
                        yPosition = change.position.y
                        touchPosition = change.position
                        val frequency = (yPosition * (maxFreq - minFreq))/screenHeight;
                        val amplitude = (1-xPosition) / screenWidth;
                        yPosFun(frequency);
                        xPosFun(amplitude)
                    },
                    onDragEnd = {
                        touchActive = false;
                        pauseFun();
                    }
                )
            }
            .pointerInput(key1 = Unit) {
                detectTapGestures(
                    onPress = { offset ->
                        val xPosition = offset.x
                        val yPosition = offset.y
                        val frequency = (yPosition * (maxFreq - minFreq)) / screenHeight
                        playFun();
                        val amplitude = (1-xPosition) / screenWidth;
                        touchPosition = offset;
                        touchActive = true;

                        yPosFun(frequency)
                        xPosFun(amplitude)
                        tryAwaitRelease()
                        pauseFun();
                        touchActive = false;
                    }
                )
            }
    ){
        drawRect(
            color = Color.Black,
            size = size
        )
        if(touchActive) {
            drawCircle(
                color = Color.Yellow, // Set the color of the circle
                radius = 90f, // Set the radius of the circle
                center = touchPosition // Use the current touch position
            )
        }
    }
}
