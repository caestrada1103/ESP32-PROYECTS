# EXAMPLE OF ADC

This code show you how to correctly use the ADC on ESP32 with ESP-IDF lenguaje.

## NOTE IMPORTANT

I tested the ADC to read an intervall of Voltage of [0-3.3]V come from a 4-20 mA conversor to Voltaje, like [this](https://electronilab.co/tienda/modulo-convertidor-de-senal-corriente-a-voltaje-4-20ma-a-0-3-3v-5v-10v/), with needed of very lowest resolution posible, but the results can be don't the expected

so, a good advice is:

1. If you want to apply any proyect with the integrate ADC on the ESP32, please don't use more of 1.1V of input voltage, this implies that the attenuation on the channel that will be used for read doesn't need to change and will get a decent linear responsive (whit 12 BIT of resolution) (this can be aplaing on General porpuse when didn't need a high accuracy ">50mV" of the measury, inclusive, if ur measury use higher steps will been consider use this with posibility of higest attenuation of 11 dB to get range of 0-3.9V ).
you can see [this](https://www.esp32.com/viewtopic.php?f=12&t=1045) forum where they explain all about this problem
2. But, you need read higher voltage that 1.1V, please consider buy external ADC with high resolution and linear responsive, only if need a high accuracy on the measure (for industrial applications with sensitive measure where need to read resolution of <10mV or lowest)
