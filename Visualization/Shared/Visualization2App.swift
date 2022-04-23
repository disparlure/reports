//
//  Visualization2App.swift
//  Shared
//
//  Created by Christine Fletcher on 4/23/22.
//

import SwiftUI

var dataElements: [Report] = []

struct Report: Identifiable {
    var id = UUID()
    var Address: String
    var Latitude: Double
    var Longitude: Double
    var VerticalSpeed: Int32
}

func load () ->Array<Report> {
    let collectionSize = getDataSize()-1
    for i in 0...collectionSize{
        var dataBuffer = Array<CChar>(repeating: 0, count: 2048)
        var lat = 0.0
        var lon = 0.0
        var vs: Int32
        vs = 0
        getDataAtIndex(Int32(i),
                       &dataBuffer,
                       &lat,
                       &lon,
                       &vs,
                       numericCast(dataBuffer.count))
        let stringrep = String(cString: dataBuffer)
        
        dataElements.append(Report(
            Address: stringrep,
            Latitude: lat,
            Longitude: lon,
            VerticalSpeed: vs))
    }
    return dataElements
}

@main
struct Visualization2App: App {
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
