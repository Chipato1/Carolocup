<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="con-wago-508" urn="urn:adsk.eagle:library:196">
<description>&lt;b&gt;Wago Screw Clamps&lt;/b&gt;&lt;p&gt;
Grid 5.08 mm&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="W237-132" urn="urn:adsk.eagle:footprint:10712/1" library_version="2">
<description>&lt;b&gt;WAGO SREW CLAMP&lt;/b&gt;</description>
<wire x1="-3.5306" y1="-1.651" x2="-1.524" y2="0.3556" width="0.254" layer="51"/>
<wire x1="1.6256" y1="-1.6764" x2="3.5306" y2="0.3556" width="0.254" layer="51"/>
<wire x1="-5.08" y1="4.191" x2="5.08" y2="4.191" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-4.826" x2="5.08" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-4.826" x2="-5.08" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="4.191" x2="-5.08" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.413" x2="-3.429" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-3.429" y1="-2.413" x2="-1.651" y2="-2.413" width="0.1524" layer="51"/>
<wire x1="-1.651" y1="-2.413" x2="1.651" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-2.413" x2="5.08" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.413" x2="-5.08" y2="-4.826" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.413" x2="5.08" y2="4.191" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="4.191" x2="-5.08" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="4.445" x2="5.08" y2="4.445" width="0.1524" layer="21"/>
<wire x1="5.08" y1="4.191" x2="5.08" y2="4.445" width="0.1524" layer="21"/>
<wire x1="1.651" y1="-2.413" x2="3.429" y2="-2.413" width="0.1524" layer="51"/>
<circle x="-2.54" y="-0.635" radius="1.4986" width="0.1524" layer="51"/>
<circle x="-2.54" y="2.8448" radius="0.508" width="0.1524" layer="21"/>
<circle x="2.54" y="-0.635" radius="1.4986" width="0.1524" layer="51"/>
<circle x="2.54" y="2.8448" radius="0.508" width="0.1524" layer="21"/>
<pad name="1" x="-2.54" y="-0.635" drill="1.1938" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="-0.635" drill="1.1938" shape="long" rot="R90"/>
<text x="-4.445" y="1.27" size="1.27" layer="51" ratio="10">1</text>
<text x="0.6858" y="1.2192" size="1.27" layer="51" ratio="10">2</text>
<text x="-3.81" y="-6.985" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-3.81" y="-4.318" size="1.27" layer="25" ratio="10">&gt;NAME</text>
</package>
</packages>
<packages3d>
<package3d name="W237-132" urn="urn:adsk.eagle:package:10734/1" type="box" library_version="2">
<description>WAGO SREW CLAMP</description>
<packageinstances>
<packageinstance name="W237-132"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="KL" urn="urn:adsk.eagle:symbol:10710/1" library_version="2">
<wire x1="1.778" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<circle x="0.889" y="0" radius="0.898" width="0.254" layer="94"/>
<text x="-1.27" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="KL+V" urn="urn:adsk.eagle:symbol:10711/1" library_version="2">
<wire x1="1.778" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<circle x="0.889" y="0" radius="0.898" width="0.254" layer="94"/>
<text x="0" y="2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="W237-02P" urn="urn:adsk.eagle:component:10750/2" prefix="X" uservalue="yes" library_version="2">
<description>&lt;b&gt;WAGO SREW CLAMP&lt;/b&gt;</description>
<gates>
<gate name="-1" symbol="KL" x="0" y="0" addlevel="always"/>
<gate name="-2" symbol="KL+V" x="0" y="-5.08" addlevel="always"/>
</gates>
<devices>
<device name="" package="W237-132">
<connects>
<connect gate="-1" pin="KL" pad="1"/>
<connect gate="-2" pin="KL" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:10734/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
<attribute name="POPULARITY" value="10" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-amp" urn="urn:adsk.eagle:library:127">
<description>&lt;b&gt;AMP Connectors&lt;/b&gt;&lt;p&gt;
RJ45 Jack connectors&lt;br&gt;
 Based on the previous libraris:
 &lt;ul&gt;
 &lt;li&gt;amp.lbr
 &lt;li&gt;amp-j.lbr
 &lt;li&gt;amp-mta.lbr
 &lt;li&gt;amp-nlok.lbr
 &lt;li&gt;amp-sim.lbr
 &lt;li&gt;amp-micro-match.lbr
 &lt;/ul&gt;
 Sources :
 &lt;ul&gt;
 &lt;li&gt;Catalog 82066 Revised 11-95 
 &lt;li&gt;Product Guide 296785 Rev. 8-99
 &lt;li&gt;Product Guide CD-ROM 1999
 &lt;li&gt;www.amp.com
 &lt;/ul&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1X12MTA" urn="urn:adsk.eagle:footprint:8080301/1" library_version="3">
<description>&lt;b&gt;AMP MTA connector&lt;/b&gt;</description>
<wire x1="23.7744" y1="6.35" x2="23.7744" y2="3.81" width="0.4064" layer="21"/>
<wire x1="23.7744" y1="3.81" x2="23.7744" y2="-3.81" width="0.4064" layer="21"/>
<wire x1="-23.8506" y1="-3.81" x2="23.7744" y2="-3.81" width="0.4064" layer="21"/>
<wire x1="-23.8506" y1="-3.81" x2="-23.8506" y2="3.81" width="0.4064" layer="21"/>
<wire x1="-23.8506" y1="3.81" x2="-23.8506" y2="6.35" width="0.4064" layer="21"/>
<wire x1="-23.8506" y1="6.35" x2="23.7744" y2="6.35" width="0.4064" layer="21"/>
<wire x1="-23.8506" y1="3.81" x2="23.7744" y2="3.81" width="0.3048" layer="21"/>
<pad name="8" x="-5.9436" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="7" x="-1.9812" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="6" x="1.9812" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="5" x="5.9436" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="4" x="9.906" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="3" x="13.8684" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="2" x="17.8308" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="1" x="21.7932" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="9" x="-9.906" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="10" x="-13.8684" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="11" x="-17.8308" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="12" x="-21.7932" y="0" drill="1.6764" shape="long" rot="R90"/>
<text x="-4.9022" y="-7.0612" size="1.778" layer="25">&gt;NAME</text>
<text x="-23.095" y="4.4508" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="21.2852" y1="-0.508" x2="22.3012" y2="0.508" layer="21"/>
<rectangle x1="17.3228" y1="-0.508" x2="18.3388" y2="0.508" layer="21"/>
<rectangle x1="13.3604" y1="-0.508" x2="14.3764" y2="0.508" layer="21"/>
<rectangle x1="9.398" y1="-0.508" x2="10.414" y2="0.508" layer="21"/>
<rectangle x1="5.4356" y1="-0.508" x2="6.4516" y2="0.508" layer="21"/>
<rectangle x1="1.4732" y1="-0.508" x2="2.4892" y2="0.508" layer="21"/>
<rectangle x1="-2.4892" y1="-0.508" x2="-1.4732" y2="0.508" layer="21"/>
<rectangle x1="-6.4516" y1="-0.508" x2="-5.4356" y2="0.508" layer="21"/>
<rectangle x1="-10.414" y1="-0.508" x2="-9.398" y2="0.508" layer="21"/>
<rectangle x1="-14.3764" y1="-0.508" x2="-13.3604" y2="0.508" layer="21"/>
<rectangle x1="-18.3388" y1="-0.508" x2="-17.3228" y2="0.508" layer="21"/>
<rectangle x1="-22.3012" y1="-0.508" x2="-21.2852" y2="0.508" layer="21"/>
</package>
<package name="1X5MTA" urn="urn:adsk.eagle:footprint:8080280/1" library_version="3">
<description>&lt;b&gt;AMP MTA connector&lt;/b&gt;</description>
<wire x1="10.16" y1="6.35" x2="10.16" y2="3.81" width="0.4064" layer="21"/>
<wire x1="10.16" y1="3.81" x2="10.16" y2="-3.81" width="0.4064" layer="21"/>
<wire x1="-10.16" y1="-3.81" x2="-10.16" y2="3.81" width="0.4064" layer="21"/>
<wire x1="-10.16" y1="3.81" x2="-10.16" y2="6.35" width="0.4064" layer="21"/>
<wire x1="-10.16" y1="6.35" x2="10.16" y2="6.35" width="0.4064" layer="21"/>
<wire x1="-10.16" y1="3.81" x2="10.16" y2="3.81" width="0.3048" layer="21"/>
<wire x1="-10.16" y1="-3.81" x2="10.16" y2="-3.81" width="0.4064" layer="21"/>
<pad name="3" x="0" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="2" x="3.9624" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="1" x="7.9248" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="4" x="-3.9624" y="0" drill="1.6764" shape="long" rot="R90"/>
<pad name="5" x="-7.9248" y="0" drill="1.6764" shape="long" rot="R90"/>
<text x="-3.7338" y="-7.0612" size="1.778" layer="25">&gt;NAME</text>
<text x="-9.4762" y="4.4508" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="7.4168" y1="-0.508" x2="8.4328" y2="0.508" layer="21"/>
<rectangle x1="3.4544" y1="-0.508" x2="4.4704" y2="0.508" layer="21"/>
<rectangle x1="-0.508" y1="-0.508" x2="0.508" y2="0.508" layer="21"/>
<rectangle x1="-4.4704" y1="-0.508" x2="-3.4544" y2="0.508" layer="21"/>
<rectangle x1="-8.4328" y1="-0.508" x2="-7.4168" y2="0.508" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="1X12MTA" urn="urn:adsk.eagle:package:8081610/1" type="box" library_version="3">
<description>&lt;b&gt;AMP MTA connector&lt;/b&gt;</description>
<packageinstances>
<packageinstance name="1X12MTA"/>
</packageinstances>
</package3d>
<package3d name="1X5MTA" urn="urn:adsk.eagle:package:8081592/1" type="box" library_version="3">
<description>&lt;b&gt;AMP MTA connector&lt;/b&gt;</description>
<packageinstances>
<packageinstance name="1X5MTA"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="MTA-12" urn="urn:adsk.eagle:symbol:8079827/1" library_version="3">
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="29.21" y1="-1.905" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="29.21" y1="-1.905" x2="29.21" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="29.21" y2="1.27" width="0.254" layer="94"/>
<circle x="0" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="5.08" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="7.62" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="10.16" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="12.7" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="15.24" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="17.78" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="20.32" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="22.86" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="25.4" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="27.94" y="0" radius="0.635" width="0.254" layer="94"/>
<text x="30.48" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="30.48" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-1.27" size="1.27" layer="95">1</text>
<pin name="1" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="3" x="5.08" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="4" x="7.62" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="5" x="10.16" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="6" x="12.7" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="7" x="15.24" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="8" x="17.78" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="9" x="20.32" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="10" x="22.86" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="11" x="25.4" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="12" x="27.94" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="MTA-05" urn="urn:adsk.eagle:symbol:8079820/1" library_version="3">
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="11.43" y1="-1.905" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="11.43" y1="-1.905" x2="11.43" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="11.43" y2="1.27" width="0.254" layer="94"/>
<circle x="0" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="5.08" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="7.62" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="10.16" y="0" radius="0.635" width="0.254" layer="94"/>
<text x="12.7" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="12.7" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-1.27" size="1.27" layer="95">1</text>
<pin name="1" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="3" x="5.08" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="4" x="7.62" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="5" x="10.16" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MTA12-156" urn="urn:adsk.eagle:component:8082769/2" prefix="J" uservalue="yes" library_version="3">
<description>&lt;b&gt;AMP connector&lt;/b&gt;</description>
<gates>
<gate name="G$6" symbol="MTA-12" x="-12.7" y="0"/>
</gates>
<devices>
<device name="" package="1X12MTA">
<connects>
<connect gate="G$6" pin="1" pad="1"/>
<connect gate="G$6" pin="10" pad="10"/>
<connect gate="G$6" pin="11" pad="11"/>
<connect gate="G$6" pin="12" pad="12"/>
<connect gate="G$6" pin="2" pad="2"/>
<connect gate="G$6" pin="3" pad="3"/>
<connect gate="G$6" pin="4" pad="4"/>
<connect gate="G$6" pin="5" pad="5"/>
<connect gate="G$6" pin="6" pad="6"/>
<connect gate="G$6" pin="7" pad="7"/>
<connect gate="G$6" pin="8" pad="8"/>
<connect gate="G$6" pin="9" pad="9"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:8081610/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="1" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MTA05-156" urn="urn:adsk.eagle:component:8082721/2" prefix="J" uservalue="yes" library_version="3">
<description>&lt;b&gt;AMP connector&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MTA-05" x="-5.08" y="0"/>
</gates>
<devices>
<device name="" package="1X5MTA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:8081592/1"/>
</package3dinstances>
<technologies>
<technology name="">
<attribute name="POPULARITY" value="0" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="X1" library="con-wago-508" library_urn="urn:adsk.eagle:library:196" deviceset="W237-02P" device="" package3d_urn="urn:adsk.eagle:package:10734/1"/>
<part name="J1" library="con-amp" library_urn="urn:adsk.eagle:library:127" deviceset="MTA12-156" device="" package3d_urn="urn:adsk.eagle:package:8081610/1"/>
<part name="J2" library="con-amp" library_urn="urn:adsk.eagle:library:127" deviceset="MTA12-156" device="" package3d_urn="urn:adsk.eagle:package:8081610/1"/>
<part name="J3" library="con-amp" library_urn="urn:adsk.eagle:library:127" deviceset="MTA12-156" device="" package3d_urn="urn:adsk.eagle:package:8081610/1"/>
<part name="J4" library="con-amp" library_urn="urn:adsk.eagle:library:127" deviceset="MTA12-156" device="" package3d_urn="urn:adsk.eagle:package:8081610/1"/>
<part name="J5" library="con-amp" library_urn="urn:adsk.eagle:library:127" deviceset="MTA05-156" device="" package3d_urn="urn:adsk.eagle:package:8081592/1"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="X1" gate="-1" x="30.48" y="58.42" smashed="yes">
<attribute name="NAME" x="29.21" y="59.309" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="X1" gate="-2" x="30.48" y="53.34" smashed="yes">
<attribute name="VALUE" x="30.48" y="55.88" size="1.778" layer="96"/>
<attribute name="NAME" x="29.21" y="54.229" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="J1" gate="G$6" x="73.66" y="66.04" smashed="yes" rot="R270">
<attribute name="NAME" x="73.66" y="35.56" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="69.85" y="35.56" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="J2" gate="G$6" x="73.66" y="33.02" smashed="yes" rot="R270">
<attribute name="NAME" x="73.66" y="2.54" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="69.85" y="2.54" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="J3" gate="G$6" x="73.66" y="-2.54" smashed="yes" rot="R270">
<attribute name="NAME" x="73.66" y="-33.02" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="69.85" y="-33.02" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="J4" gate="G$6" x="73.66" y="-38.1" smashed="yes" rot="R270">
<attribute name="NAME" x="73.66" y="-68.58" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="69.85" y="-68.58" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="J5" gate="G$1" x="73.66" y="-73.66" smashed="yes" rot="R270">
<attribute name="NAME" x="73.66" y="-86.36" size="1.778" layer="95" rot="R270"/>
<attribute name="VALUE" x="69.85" y="-86.36" size="1.778" layer="96" rot="R270"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="J4" gate="G$6" pin="8"/>
<pinref part="J4" gate="G$6" pin="7"/>
<wire x1="71.12" y1="-55.88" x2="71.12" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="J4" gate="G$6" pin="6"/>
<pinref part="J4" gate="G$6" pin="5"/>
<wire x1="71.12" y1="-50.8" x2="71.12" y2="-48.26" width="0.1524" layer="91"/>
<pinref part="X1" gate="-2" pin="KL"/>
<pinref part="J3" gate="G$6" pin="1"/>
<wire x1="35.56" y1="53.34" x2="35.56" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-2.54" x2="63.5" y2="-2.54" width="0.1524" layer="91"/>
<pinref part="J4" gate="G$6" pin="1"/>
<wire x1="63.5" y1="-2.54" x2="71.12" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-2.54" x2="35.56" y2="-38.1" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-38.1" x2="71.12" y2="-38.1" width="0.1524" layer="91"/>
<junction x="35.56" y="-2.54"/>
<pinref part="J5" gate="G$1" pin="5"/>
<wire x1="71.12" y1="-83.82" x2="60.96" y2="-83.82" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-83.82" x2="60.96" y2="-81.28" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-81.28" x2="60.96" y2="-78.74" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-78.74" x2="60.96" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-76.2" x2="60.96" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-73.66" x2="60.96" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="J5" gate="G$1" pin="4"/>
<wire x1="71.12" y1="-81.28" x2="60.96" y2="-81.28" width="0.1524" layer="91"/>
<junction x="60.96" y="-81.28"/>
<pinref part="J5" gate="G$1" pin="3"/>
<wire x1="71.12" y1="-78.74" x2="60.96" y2="-78.74" width="0.1524" layer="91"/>
<junction x="60.96" y="-78.74"/>
<pinref part="J5" gate="G$1" pin="2"/>
<wire x1="71.12" y1="-76.2" x2="60.96" y2="-76.2" width="0.1524" layer="91"/>
<junction x="60.96" y="-76.2"/>
<pinref part="J5" gate="G$1" pin="1"/>
<wire x1="71.12" y1="-73.66" x2="60.96" y2="-73.66" width="0.1524" layer="91"/>
<junction x="60.96" y="-73.66"/>
<wire x1="35.56" y1="-38.1" x2="35.56" y2="-40.64" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-40.64" x2="35.56" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-43.18" x2="35.56" y2="-50.8" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-50.8" x2="35.56" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-55.88" x2="35.56" y2="-58.42" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-58.42" x2="35.56" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-63.5" x2="35.56" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-66.04" x2="60.96" y2="-66.04" width="0.1524" layer="91"/>
<junction x="35.56" y="-38.1"/>
<pinref part="J4" gate="G$6" pin="11"/>
<wire x1="71.12" y1="-63.5" x2="35.56" y2="-63.5" width="0.1524" layer="91"/>
<junction x="35.56" y="-63.5"/>
<pinref part="J4" gate="G$6" pin="10"/>
<wire x1="71.12" y1="-60.96" x2="71.12" y2="-58.42" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-58.42" x2="35.56" y2="-58.42" width="0.1524" layer="91"/>
<junction x="35.56" y="-58.42"/>
<pinref part="J4" gate="G$6" pin="9"/>
<junction x="71.12" y="-58.42"/>
<pinref part="J4" gate="G$6" pin="4"/>
<wire x1="71.12" y1="-45.72" x2="71.12" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-43.18" x2="35.56" y2="-43.18" width="0.1524" layer="91"/>
<junction x="35.56" y="-43.18"/>
<pinref part="J4" gate="G$6" pin="3"/>
<junction x="71.12" y="-43.18"/>
<pinref part="J4" gate="G$6" pin="2"/>
<wire x1="71.12" y1="-40.64" x2="35.56" y2="-40.64" width="0.1524" layer="91"/>
<junction x="35.56" y="-40.64"/>
<wire x1="71.12" y1="-50.8" x2="35.56" y2="-50.8" width="0.1524" layer="91"/>
<junction x="71.12" y="-50.8"/>
<junction x="35.56" y="-50.8"/>
<wire x1="71.12" y1="-55.88" x2="35.56" y2="-55.88" width="0.1524" layer="91"/>
<junction x="71.12" y="-55.88"/>
<junction x="35.56" y="-55.88"/>
<pinref part="J4" gate="G$6" pin="12"/>
<wire x1="71.12" y1="-66.04" x2="60.96" y2="-66.04" width="0.1524" layer="91"/>
<junction x="60.96" y="-66.04"/>
<pinref part="J3" gate="G$6" pin="12"/>
<wire x1="71.12" y1="-30.48" x2="63.5" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-30.48" x2="63.5" y2="-27.94" width="0.1524" layer="91"/>
<junction x="63.5" y="-2.54"/>
<pinref part="J3" gate="G$6" pin="11"/>
<wire x1="63.5" y1="-27.94" x2="63.5" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-25.4" x2="63.5" y2="-22.86" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-22.86" x2="63.5" y2="-20.32" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-20.32" x2="63.5" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-17.78" x2="63.5" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-15.24" x2="63.5" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-12.7" x2="63.5" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-10.16" x2="63.5" y2="-7.62" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-7.62" x2="63.5" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-5.08" x2="63.5" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-27.94" x2="63.5" y2="-27.94" width="0.1524" layer="91"/>
<junction x="63.5" y="-27.94"/>
<pinref part="J3" gate="G$6" pin="10"/>
<wire x1="71.12" y1="-25.4" x2="63.5" y2="-25.4" width="0.1524" layer="91"/>
<junction x="63.5" y="-25.4"/>
<pinref part="J3" gate="G$6" pin="9"/>
<wire x1="71.12" y1="-22.86" x2="63.5" y2="-22.86" width="0.1524" layer="91"/>
<junction x="63.5" y="-22.86"/>
<pinref part="J3" gate="G$6" pin="8"/>
<wire x1="71.12" y1="-20.32" x2="63.5" y2="-20.32" width="0.1524" layer="91"/>
<junction x="63.5" y="-20.32"/>
<pinref part="J3" gate="G$6" pin="7"/>
<wire x1="71.12" y1="-17.78" x2="63.5" y2="-17.78" width="0.1524" layer="91"/>
<junction x="63.5" y="-17.78"/>
<pinref part="J3" gate="G$6" pin="6"/>
<wire x1="71.12" y1="-15.24" x2="63.5" y2="-15.24" width="0.1524" layer="91"/>
<junction x="63.5" y="-15.24"/>
<pinref part="J3" gate="G$6" pin="5"/>
<wire x1="71.12" y1="-12.7" x2="63.5" y2="-12.7" width="0.1524" layer="91"/>
<junction x="63.5" y="-12.7"/>
<pinref part="J3" gate="G$6" pin="4"/>
<wire x1="71.12" y1="-10.16" x2="63.5" y2="-10.16" width="0.1524" layer="91"/>
<junction x="63.5" y="-10.16"/>
<pinref part="J3" gate="G$6" pin="3"/>
<wire x1="71.12" y1="-7.62" x2="63.5" y2="-7.62" width="0.1524" layer="91"/>
<junction x="63.5" y="-7.62"/>
<pinref part="J3" gate="G$6" pin="2"/>
<wire x1="71.12" y1="-5.08" x2="63.5" y2="-5.08" width="0.1524" layer="91"/>
<junction x="63.5" y="-5.08"/>
<label x="38.1" y="40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="X1" gate="-1" pin="KL"/>
<pinref part="J1" gate="G$6" pin="1"/>
<wire x1="35.56" y1="58.42" x2="35.56" y2="66.04" width="0.1524" layer="91"/>
<wire x1="35.56" y1="66.04" x2="58.42" y2="66.04" width="0.1524" layer="91"/>
<pinref part="J2" gate="G$6" pin="1"/>
<wire x1="58.42" y1="66.04" x2="71.12" y2="66.04" width="0.1524" layer="91"/>
<wire x1="71.12" y1="33.02" x2="58.42" y2="33.02" width="0.1524" layer="91"/>
<wire x1="58.42" y1="33.02" x2="58.42" y2="38.1" width="0.1524" layer="91"/>
<junction x="58.42" y="66.04"/>
<pinref part="J2" gate="G$6" pin="12"/>
<wire x1="58.42" y1="38.1" x2="58.42" y2="40.64" width="0.1524" layer="91"/>
<wire x1="58.42" y1="43.18" x2="58.42" y2="45.72" width="0.1524" layer="91"/>
<wire x1="58.42" y1="45.72" x2="58.42" y2="48.26" width="0.1524" layer="91"/>
<wire x1="58.42" y1="48.26" x2="58.42" y2="50.8" width="0.1524" layer="91"/>
<wire x1="58.42" y1="50.8" x2="58.42" y2="53.34" width="0.1524" layer="91"/>
<wire x1="58.42" y1="53.34" x2="58.42" y2="55.88" width="0.1524" layer="91"/>
<wire x1="58.42" y1="55.88" x2="58.42" y2="58.42" width="0.1524" layer="91"/>
<wire x1="58.42" y1="58.42" x2="58.42" y2="60.96" width="0.1524" layer="91"/>
<wire x1="58.42" y1="60.96" x2="58.42" y2="63.5" width="0.1524" layer="91"/>
<wire x1="58.42" y1="63.5" x2="58.42" y2="66.04" width="0.1524" layer="91"/>
<wire x1="71.12" y1="5.08" x2="58.42" y2="5.08" width="0.1524" layer="91"/>
<wire x1="58.42" y1="5.08" x2="58.42" y2="7.62" width="0.1524" layer="91"/>
<junction x="58.42" y="33.02"/>
<pinref part="J2" gate="G$6" pin="11"/>
<wire x1="58.42" y1="7.62" x2="58.42" y2="10.16" width="0.1524" layer="91"/>
<wire x1="58.42" y1="10.16" x2="58.42" y2="12.7" width="0.1524" layer="91"/>
<wire x1="58.42" y1="12.7" x2="58.42" y2="15.24" width="0.1524" layer="91"/>
<wire x1="58.42" y1="15.24" x2="58.42" y2="17.78" width="0.1524" layer="91"/>
<wire x1="58.42" y1="17.78" x2="58.42" y2="20.32" width="0.1524" layer="91"/>
<wire x1="58.42" y1="20.32" x2="58.42" y2="22.86" width="0.1524" layer="91"/>
<wire x1="58.42" y1="22.86" x2="58.42" y2="25.4" width="0.1524" layer="91"/>
<wire x1="58.42" y1="25.4" x2="58.42" y2="27.94" width="0.1524" layer="91"/>
<wire x1="58.42" y1="27.94" x2="58.42" y2="30.48" width="0.1524" layer="91"/>
<wire x1="58.42" y1="30.48" x2="58.42" y2="33.02" width="0.1524" layer="91"/>
<wire x1="71.12" y1="7.62" x2="58.42" y2="7.62" width="0.1524" layer="91"/>
<junction x="58.42" y="7.62"/>
<pinref part="J2" gate="G$6" pin="10"/>
<wire x1="71.12" y1="10.16" x2="58.42" y2="10.16" width="0.1524" layer="91"/>
<junction x="58.42" y="10.16"/>
<pinref part="J2" gate="G$6" pin="9"/>
<wire x1="71.12" y1="12.7" x2="58.42" y2="12.7" width="0.1524" layer="91"/>
<junction x="58.42" y="12.7"/>
<pinref part="J2" gate="G$6" pin="8"/>
<wire x1="71.12" y1="15.24" x2="58.42" y2="15.24" width="0.1524" layer="91"/>
<junction x="58.42" y="15.24"/>
<pinref part="J2" gate="G$6" pin="7"/>
<wire x1="71.12" y1="17.78" x2="58.42" y2="17.78" width="0.1524" layer="91"/>
<junction x="58.42" y="17.78"/>
<pinref part="J2" gate="G$6" pin="6"/>
<wire x1="71.12" y1="20.32" x2="58.42" y2="20.32" width="0.1524" layer="91"/>
<junction x="58.42" y="20.32"/>
<pinref part="J2" gate="G$6" pin="5"/>
<wire x1="71.12" y1="22.86" x2="58.42" y2="22.86" width="0.1524" layer="91"/>
<junction x="58.42" y="22.86"/>
<pinref part="J2" gate="G$6" pin="4"/>
<wire x1="71.12" y1="25.4" x2="58.42" y2="25.4" width="0.1524" layer="91"/>
<junction x="58.42" y="25.4"/>
<pinref part="J2" gate="G$6" pin="3"/>
<wire x1="71.12" y1="27.94" x2="58.42" y2="27.94" width="0.1524" layer="91"/>
<junction x="58.42" y="27.94"/>
<pinref part="J2" gate="G$6" pin="2"/>
<wire x1="71.12" y1="30.48" x2="58.42" y2="30.48" width="0.1524" layer="91"/>
<junction x="58.42" y="30.48"/>
<pinref part="J1" gate="G$6" pin="12"/>
<wire x1="71.12" y1="38.1" x2="58.42" y2="38.1" width="0.1524" layer="91"/>
<junction x="58.42" y="38.1"/>
<pinref part="J1" gate="G$6" pin="11"/>
<wire x1="71.12" y1="40.64" x2="58.42" y2="40.64" width="0.1524" layer="91"/>
<wire x1="58.42" y1="40.64" x2="58.42" y2="43.18" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$6" pin="10"/>
<wire x1="71.12" y1="43.18" x2="58.42" y2="43.18" width="0.1524" layer="91"/>
<junction x="58.42" y="43.18"/>
<pinref part="J1" gate="G$6" pin="9"/>
<wire x1="71.12" y1="45.72" x2="58.42" y2="45.72" width="0.1524" layer="91"/>
<junction x="58.42" y="45.72"/>
<pinref part="J1" gate="G$6" pin="8"/>
<wire x1="71.12" y1="48.26" x2="58.42" y2="48.26" width="0.1524" layer="91"/>
<junction x="58.42" y="48.26"/>
<pinref part="J1" gate="G$6" pin="7"/>
<wire x1="71.12" y1="50.8" x2="58.42" y2="50.8" width="0.1524" layer="91"/>
<junction x="58.42" y="50.8"/>
<junction x="58.42" y="53.34"/>
<pinref part="J1" gate="G$6" pin="6"/>
<wire x1="71.12" y1="53.34" x2="58.42" y2="53.34" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$6" pin="5"/>
<wire x1="71.12" y1="55.88" x2="58.42" y2="55.88" width="0.1524" layer="91"/>
<junction x="58.42" y="55.88"/>
<pinref part="J1" gate="G$6" pin="4"/>
<wire x1="71.12" y1="58.42" x2="58.42" y2="58.42" width="0.1524" layer="91"/>
<junction x="58.42" y="58.42"/>
<pinref part="J1" gate="G$6" pin="3"/>
<wire x1="71.12" y1="60.96" x2="58.42" y2="60.96" width="0.1524" layer="91"/>
<junction x="58.42" y="60.96"/>
<pinref part="J1" gate="G$6" pin="2"/>
<wire x1="71.12" y1="63.5" x2="58.42" y2="63.5" width="0.1524" layer="91"/>
<junction x="58.42" y="63.5"/>
<label x="40.64" y="68.58" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
