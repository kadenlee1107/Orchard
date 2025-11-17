import Foundation

struct ShaderJob: Codable {
    let input: String
    let output: String
}

@main
struct ShaderCompiler {
    static func main() async throws {
        let data = FileHandle.standardInput.readDataToEndOfFile()
        let jobs = try JSONDecoder().decode([ShaderJob].self, from: data)
        for job in jobs {
            let task = Process()
            task.executableURL = URL(fileURLWithPath: "/usr/bin/xcrun")
            task.arguments = ["-sdk", "macosx", "metal", job.input, "-o", job.output]
            try task.run()
            task.waitUntilExit()
        }
    }
}
