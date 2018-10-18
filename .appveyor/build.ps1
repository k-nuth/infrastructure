# python build.py


If ($env:WAIT_FOR_DEPS -eq 1) {
    conan user
    conan remote add bitprim_temp https://api.bintray.com/conan/bitprim/bitprim
    echo "waiting for secp256k1/0.X@bitprim/staging ..."
    conan search secp256k1/0.X@bitprim/staging -r bitprim_temp > $null
    while($env:lastExitCode -eq 1) {
        Write-Host "."
        Start-Sleep -s 10
        conan search secp256k1/0.X@bitprim/staging -r bitprim_temp > $null
    }
    Write-Host "secp256k1/0.X@bitprim/staging found"
}
Else {
    python build.py
}