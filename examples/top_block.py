#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Fri Jul  4 21:36:31 2014
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from gnuradio.wxgui import numbersink2
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import test1
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.configured_frequency = configured_frequency = 500

        ##################################################
        # Blocks
        ##################################################
        _configured_frequency_sizer = wx.BoxSizer(wx.VERTICAL)
        self._configured_frequency_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_configured_frequency_sizer,
        	value=self.configured_frequency,
        	callback=self.set_configured_frequency,
        	label='configured_frequency',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._configured_frequency_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_configured_frequency_sizer,
        	value=self.configured_frequency,
        	callback=self.set_configured_frequency,
        	minimum=2,
        	maximum=2000,
        	num_steps=999,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_configured_frequency_sizer)
        self.wxgui_scopesink2_0_0 = scopesink2.scope_sink_f(
        	self.GetWin(),
        	title="Scope Plot",
        	sample_rate=samp_rate,
        	v_scale=500,
        	v_offset=0,
        	t_scale=2.5e-3,
        	ac_couple=False,
        	xy_mode=False,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.Add(self.wxgui_scopesink2_0_0.win)
        self.wxgui_numbersink2_0 = numbersink2.number_sink_f(
        	self.GetWin(),
        	unit="Units",
        	minval=-100,
        	maxval=100,
        	factor=1.0,
        	decimal_places=10,
        	ref_level=0,
        	sample_rate=samp_rate,
        	number_rate=15,
        	average=False,
        	avg_alpha=None,
        	label="Number Plot",
        	peak_hold=False,
        	show_gauge=True,
        )
        self.Add(self.wxgui_numbersink2_0.win)
        self.test1_freq_counter2_0 = test1.freq_counter2(samp_rate, 0.1)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_COS_WAVE, configured_frequency, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.test1_freq_counter2_0, 0))
        self.connect((self.test1_freq_counter2_0, 0), (self.wxgui_numbersink2_0, 0))
        self.connect((self.test1_freq_counter2_0, 0), (self.wxgui_scopesink2_0_0, 0))



    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.wxgui_scopesink2_0_0.set_sample_rate(self.samp_rate)

    def get_configured_frequency(self):
        return self.configured_frequency

    def set_configured_frequency(self, configured_frequency):
        self.configured_frequency = configured_frequency
        self.analog_sig_source_x_0.set_frequency(self.configured_frequency)
        self._configured_frequency_slider.set_value(self.configured_frequency)
        self._configured_frequency_text_box.set_value(self.configured_frequency)

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()
