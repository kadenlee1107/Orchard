import Foundation

struct ImportTask: Codable {
    let source: String
    let uuid: String
}

@main
struct AssetPipeline {
    static func main() throws {
        let input = FileHandle.standardInput.readDataToEndOfFile()
        let tasks = try JSONDecoder().decode([ImportTask].self, from: input)
        for task in tasks {
            let destination = URL(fileURLWithPath: "Build/\(task.uuid).orchardpkg")
            try? FileManager.default.createDirectory(at: destination.deletingLastPathComponent(), withIntermediateDirectories: true)
            try Data(contentsOf: URL(fileURLWithPath: task.source)).write(to: destination)
        }
    }
}
