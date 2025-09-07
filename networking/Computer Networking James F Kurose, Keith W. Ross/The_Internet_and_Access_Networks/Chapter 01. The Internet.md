## 1.1 What is the internet?
The internet is an computer network of numerous interconnected computing devices, Its aim is to exchange information across our world.

These devices that connect to the internet are known as **hosts or end systems**. End systems are connected with each other by communication links and packet-switches.

Communication links transfer data at a rate known as **transmission-rate**, measured in bits/sec. 

In a situation that an end system wishes to send data form one point to another in a network, It prepares the data, breaks it into chunks, and adds extra bits to the data known as headers to the data, this holistic preparation consisting of chunks of data plus the added header are known as **packets**. 

A **Packet Switch** is the relay that takes packets coming from one of its incoming communication links and sends that packets to one of it’s outgoing communication links. The 2  prominent types of packet switches are *routers and link-layer switches*. 

The pathways of communication links and packet switches that a packet traverses from its propagated end system to the target end-system is known as it’s ***route or path**

End-systems access the internet via **Internet Service Providers (ISPs)**, ISPs themselves are networks with packet switches and communication links.

End systems, packet switches and other components of the internet run on **Protocols**, they dictate how data is sent in a network. The 2 protocols that serves as the backbone of the internet are the **Transmission Control Protocol (TCP)**  and  the **Internet Protocol**.

The IP protocol specify the format of the packets that sent and received among routers and end systems.

## 1.1.2 A Service Description
Internet applications run on end systems, and those applications can be referred to as **Distributed Systems** since they are composed of different application of the internet involving multiple end systems and networks that exchange information between each other.

End Systems attached to the internet provide **Socket Interfaces**, that describe how a program running on an end systems would interface, via the **Internet Infrastructure**, with another program running on another end system.

This internet Socket interface provides rules that enables data from one end systems to be sent to another end system via the internet.

## 1.1.3 What is a protocol

A protocol defines the order and format of messages to be transferred between two communicating entities as well as the action to be taking on the transfer or receipt of the message/event.

# 1.2 The Network Edge
End-systems are referred to as such because they sit at the end of the internet. They are also referred to as **Hosts** because they run some certain application program e.g Browser.
*Servers* are host that serve some information and *Clients* are hosts that receive said information.

## 1.2.1 Access Networks
These are Networks that physically connect end-systems to the first router (edge router) on the path of the end-system to any other distant end-system.

Types of access Networks: 
* Home Access Networks: DSL, Cable, FTTH and 5G Fixed Wireless
* Access Networks in Enterprises (And Home): Ethernet and WiFi
* Wide-Area Wireless Access: 3G and LTE, 4G and 5G.

### Home access Network

#### DIgital Subscriber Line Networks
The two prevalent options in which home connect to the internet are **Digital Subscriber Line (DSL)** and cable. Residences often obtain DSL internet access from the same telephone company they use, ergo the customers telephone company identifier  is also its ISP.

Now each customers **DSL**ine modem uses their existing telephone line to exchange data with a **DSL**ine access Multiplexer (DSLAM) located at the telcos local central office (CO), the homes DSL modem takes digital data and translates it to high frequency tones to be sent via the telephone lines to the DSLAM  of the local central office; 

The central office picks up many analog signals form numerous homes which are translated back to digital format at the DSLAM.

Residential telephone lines carry both data and traditional telephone signals simultaneously each encoded at different frequencies:
* High speed downstream channel → 50KHz to 1MHz band
* Medium speed upstream channel → 4KHz to 50KHz band
* Ordinary two way telephone channel → 0 to 4KHz band
This approach makes a single DSLS link appea appear as a single link, so that telephone call an internet connection can happen simultaneously.

On the customer side the splitter splits this frequency bands from data and telephone, and forwards the telepone signals to the DSL modem, providing internet.

And on the telco side, the DSLAM separates data and phone signals and sends the data to the internet.

![DSL Internet](imgs/DSL%20Internet.png)

Network quality of a residence in a this network is affected by their proximity to the nearest local telcos central office and other interference that happen at the phone lines.

#### Cable Networks
While DSL makes use of the telcos existing local telephone infrastructure, cable internet access makes use of the cable televisions company existing cable television infrastructure.

![Cable internet](imgs/Cable%20internet.png)

Cable internet require special modems known as cable modems, It is an external device that connects to the Home Pcs via an Ethernet port. 

At the Cable Head, the **Cable Modem Termination System** functions similarly to the DSL networks DSLAM, Cable modems divide **Hybrid Fiber Coaxial Network** (which is the transmission technology used in Cable Network) into 2 channel; upstream and downstream, which it’s access are asymmetric.

AN important feature of Cable Internet  Access is it’s shared broadcast medium; Meaning every packet sent by the Cable head travels downstream to every home connected, And every packet uploaded by a home travel upstream to the cable head, meaning; if multiple residences are requesting the same data (e.g downloading the same video), the rate would be affected by the factor of the concurrent requests of the video, everyone’s fighting for the same bone.

#### Fiber To The Home FTTH
Due to the limitations of both DSL and cable internet, an alternative emerged, FTTH, its philosophy is simple; provide direct optical fiber path form the CO directly to the home, It can potentially provide internet access rates in gigabits per second.

### Access in Enterprise Networks (And the Home): Ethernet and WiFi
This paradigm is popular in university campuses and home settings, basically a Local Area Network is used to connect an end-system,to the edge router. 

The LAN network could either be composed of an Ethernet or WiFi Network, making it either wired or wireless.

![Ethernet Internet acess](imgs/Ethernet%20Internet%20acess.png)


## 1.2.2 Physical Media
There a several physical mediums bits traverse through while propagating in a network they could be:
1) Twisted-pair copper wire
2) Coaxial cable
3) Multi-mode fiber-optic cable
4) Terrestrial radio spectrum
5) Satellite radio spectrum

Physical mediums, themselves fall into two categories:
1) Guided Media: A solid medium e.g fiber optic cable
2) Unguided Media: Through the atmosphere or outer space e.g wireless LAN

### Twisted pair copper Wire
This is the least expensive and most popularly used transmission medium. It consists of two insulated copper wires, usually 1mm thick, arranged in a spiral pattern.

The wires are twisted together to reduce electrical interference from similar pair close by. Typically a number of pairs are bundled together in a cable by wrapping the pairs in a protective shield.

A wire pair constitutes a single communication link. 

**Unshielded twisted pair** (UTP) is commonly used for computer networks within a building for LANs, data rates with twisted pair today can range from 10Mbs to 10Gbs.

### Coaxial Cable
Just like twisted this consists of two copper wires, but instead of having a twisted parallel configuration both wires are concentric with one another and a separated by a special insulator. Both wires are also specially shielded.

They are used in Cable TV/Internet Networks. The can be used to provide a guided shared medium, which numerous end systems are connected by a coaxial cable in a Network in which whatever is sent by a single end system is received by all other end systems.

### Fiber Optics
An Optical Fiber is a thin, flexible medium that conducts pulses of light in which each pulse represents a bit. A single optical fiber can support tremendous but rates, up to 10-100GBps.

They are immune to electromagnetic interference, They also posses low signal attenuation up to 100 kilometers and are very hard to tap.

They are expensive though. The Optical Carrier standard link speeds range from 51.8 Mbs to 39.8Gbs; These specification are often referred to as OC-*n*, where the link speed $n * 51.8Mbs$. There are a lot of crazy standards bra e.g `OC-768`

### Terrestrial Radio Channels
Radio channels carry signals in the electromagnetic spectrum. They are attractive because the require no physical medium ergo they can pass through physical obstructions like walls.

The characteristics of radio channel signals depend on the environment of its propagation and the distance of its target. 

These environmental considerations determine:
* **Path loss and shadow fading** which decrease the quality of the signal travel distances and are obstructed by barriers (walls)
* **Multi-path fading** due to signal reflection off interfering objects, and
* **Interference** due to other electromagnetic transmissions.

Terrestrial radio channels can be broadly classified into three groups; 
1) those that operate over very short distances; 
2) those the operate in local areas and 
3) those that operate in wide areas

### Satellite Radio Channels
A **communication satellites** links two or more earth based microwave transmitters or receivers known as **ground stations**

The satellites receives transmission in one frequency band, regenerates the transmission in using a repeater and transmits the signal in another frequency.

Two types of satellites are used in communications:
1) Geostationary satellites and → permanent position above the earth (36’000km away)
2) Low-earth orbiting satellites (LEO) → closer and not permanent in position

Due to the large distance between geostationary satellites and the earth, A delay of 280 milliseconds is observed when signal is sent to by a ground station it and its response is awaited.

LEO satellites on the other hand are much closer to earth, and rotate around it just like the moon. They may communicate with each other, as well as with ground stations.



