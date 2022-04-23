//
//  ContentView.swift
//  Shared
//
//  Created by Christine Fletcher on 4/23/22.
//

import SwiftUI



extension Report {
    
}
private class ReportsViewModel: ObservableObject {
    @Published var reports: [Report] = load()
}

let formatter: NumberFormatter = {
    let formatter = NumberFormatter()
    formatter.numberStyle = .decimal
    return formatter
}()

struct ContentView: View {
    @StateObject fileprivate var viewModel = ReportsViewModel()
    var body: some View {
        List(viewModel.reports) { rep in
            VStack(alignment: .leading, spacing: 7) {
                Text("\(rep.Address)")
                    .bold()
                Divider()
                HStack {
                    Text("Lat:\(rep.Latitude, specifier: "%.3f")")
                        .frame(width: 90, height: 20, alignment: Alignment.center)
                        .font(.system(size: 14))
                        .clipped()
                    Text("Lon:\(rep.Longitude, specifier: "%.3f")")
                        .frame(width: 90, height: 20, alignment: Alignment.center)
                        .font(.system(size: 14))
                        .clipped()
                    Text("VS:\(rep.VerticalSpeed)")
                        .frame(width: 70, height: 20, alignment: Alignment.center)
                        .clipped()
                        .font(.system(size: 14))
                }
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
