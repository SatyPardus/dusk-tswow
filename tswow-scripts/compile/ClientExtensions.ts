import { Args } from "../util/Args";
import { ipaths } from "../util/Paths";
import { isWindows } from "../util/Platform";
import { wsys } from "../util/System";
import { bpaths, spaths } from "./CompilePaths";
import { DownloadFile } from "./Downloader";

export namespace ClientExtensions {
    const validModes = ["Release", "Debug", "RelWithDebInfo"];

    export async function create(cmake: string, compileArgs: string[]) {
        if(isWindows())
        {
            const compileMode = compileArgs.find(arg => Args.hasFlag([arg],validModes) || "Release")
            // build locally
            wsys.exec(`${cmake} `
            + `-A Win32`
            + ` -S "${spaths.misc.client_extensions.abs().get()}" `
            + ` -B "${bpaths.client_extensions.abs().get()}"`
            + ` -DBOOST_ROOT="${bpaths.boost.boost_1_82_0.abs().get()}"`
            , 'inherit');

            wsys.exec(`${cmake}`
                + ` --build "${bpaths.client_extensions.abs().get()}"`
                + ` --config ${compileMode}`
                , 'inherit');
            switch(compileMode)
            {
                case validModes[0]:
                    bpaths.client_extensions.dll_path_rel.copy(ipaths.bin.ClientExtensions_dll)
                    break;
                case validModes[1]:
                    bpaths.client_extensions.dll_path_deb.copy(ipaths.bin.ClientExtensions_dll)
                    break;
                case validModes[2]:
                    bpaths.client_extensions.dll_path_rel_with_deb.copy(ipaths.bin.ClientExtensions_dll)
                    break;
            } 
        }
        else
        {
            // download prebuild
            await DownloadFile(
                'https://github.com/tswow/misc/releases/download/client-extensions-test/ClientExtensions.dll'
                , bpaths.ClientExtensionsDll
            );
            bpaths.ClientExtensionsDll.copy(ipaths.bin.ClientExtensions_dll)
        }
    }
}