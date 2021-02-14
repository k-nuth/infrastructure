// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CRYPTO_TEST_HASH_HPP
#define KTH_CRYPTO_TEST_HASH_HPP

#include <string>
#include <vector>

struct hash_result
{
    std::string input, result;
};

struct pkcs5_pbkdf2_hmac_sha512_result
{
    std::string passphrase, salt;
    size_t iterations;
    std::string result;
};

using hash_result_list = std::vector<hash_result>;
using pkcs5_pbkdf2_hmac_sha512_result_list = std::vector<pkcs5_pbkdf2_hmac_sha512_result>;

hash_result_list sha1_tests{{
    {"", "da39a3ee5e6b4b0d3255bfef95601890afd80709"},
    {"27ed20cb2fa1c9093ebf82427b2abff42cbd", "6a56c8684a4a5f37fee6d91526696aded7c0aa0a"},
    {"ddba0a9bc3e53d6ef1c34c11031b54fdce18d54d0c2fb59fc80f0af4314e6916d0b0c5ae9ad8", "68e277e7fa9bc9d5ccfbceb08f57cf83fde883c0"},
    {"aa9224a8e046e5b2", "ff409fff25b6ae55ac96994427eab6eaafd67559"},
    {"14b7ae683c371ccd6436f4742075578dc599dfc3a437ec8b", "36759eabb931b80fbbca8e6e533fca72388bd8f2"},
    {"f9c8eda189222a4e46f65c36a64cae11b26aa531121aa6697fd93504f9aecac893a47dd9", "7e619f364df8159ed0e55edeb5008d77cbfb7574"},
    {"e35af7be6135f20cebee722c6cdbafe8620a7cd796d3fbf6ac1cf81eae17faeebe80", "4c8770cb9f6ed23b4603990de3b12f1ec437f1bf"},
    {"fdac4bc3951ee0ebad89ce3806496468ce495c91b1f2e206822cf18ebe3c8bd1319e1ef87d", "abc658273513f036231c3ac93d693e520ba289cf"},
    {"a04117c5defe8bdc4be999f3c8889f74af9429ef2a6808c462b48c8400a8ac4bf1397ccfcff0e03ebd", "f12c13bcc078f864baf9eda3a0f551828006cab9"},
    {"46bf37cf595b18e6553ee97254734a7a704c6db89833cd5ebe7fdf8659", "4840799d2cd8ede95c43e701530c83f84cdbd31c"},
    {"c158cd2ed7c0dced347c1f9a619d1c8dc382b4e539400cc9aefb97d6083a141c", "b3bedc3d40dbd0991d31af668f2bc946fe2cc2b5"},
    {"1848614e29ff5920e8a7e1ba31fcd2c2c3c7d07b7c", "2a5a51e2f2e1c90b303054fe41f57bd25258a13c"},
    {"b34d4bef16f613861b7ad624ebdebd99517e", "9f0cefbc13cd853394c7b02de97f5f436ea3918d"},
    {"4ee01f8feee0a6ac275f58b85ceab49c603b78ff606703cab57c52fc7617930366a56c5daed2f3e17e0ee2da4ce8b8", "17ecd1fb6df59261017650bc1fd8dffb11594d3f"},
    {"a7afbeb9491d91d679f843c7", "d6ad4a2a306137c7851dc6ef9b2fd0af20ecbfd1"},
    {"821161f3c04b6b11c4d1a4", "128a1700ae4590fe7b982a53b16334190f21c4b7"},
    {"d9cdc2bb692281ea033489ab4cf08a0ea7e934edb4f9b135bcdae7da484c399e463490", "7848f419a5da361142fc46646866272bfa7c6552"},
    {"99a74cb1645b7ed583a5c077a0545586f55cb2629109b7f10dce77a91ef3285c", "c5ddea4614c2655844f6597fabb64230e2e8232b"},
    {"cb9779", "33274f991e78de247db476c70d88f889c23cd0eb"},
    {"0b681b18aa5a44b9a1b245ed10", "61e8608b603391ac90a543d3b531662ccef29f16"},
    {"70206feaa65059d63e2d5807f92b49e3ce183ba3c4185c03944e6a366119409873cf", "643ca9c7b4774128514be660c0304d4dec5cc7ca"}
}};

hash_result_list sha256_tests{{
    {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
    {"f0d5e1ba902e341a58320a08078af4311e1291dcffd97f00c06988e0e26a071832", "1f23e6ce087e16c4f3585fbe89a4be22961b413076eea1621a81fefaf0c33ecc"},
    {"a5c082e4489c6aa415a961a1e2d0cbf12ed671e5d10d97fb6e63b852b056396670c336d21c75eca4ab0527023b59656a2136", "ad794747682bf286993167ba8b46a0c2b3ad888b91f2917e29832bee1261fcf0"},
    {"c7cbf76a7f875446a32bc8c2a7ce295e1acf85eb10ad66c682b154f08acaa10262ef", "997b848f26a6de7efd214c47f0d56dc95b656ec519ebded493f51c2f5166dbb6"},
    {"2a3333448873620c921c47ae387b1768c7b5227fdb4af5512756a6ba0eab6e84be95da98", "15fbe855e1343185950e6d8b6d907c24e3d8f0d769be537d8b8f239ae33c8926"},
    {"650fb10d5d392f14456bf2f301e8af92bb8a51164b28", "e7abad46a85893bf44e464626473b432ca4e87c94b1e462270ba313d16441bf5"},
    {"0c8fd399", "e2d710db0ccb875f2069683862f743312a5ed223d1e209f5ec27becb9821226a"},
    {"9aa42e8eb0bd", "13ed61ce40d00e1c50573392f16170afd77c43c34211e3f601f044059c3377e3"},
    {"4512b0693593a91b02b06bf0c137", "f0b0c8dfdcc4e31e756a820066e61e383c4159da3278baee23aeb4cfb5add765"},
    {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
    {"98d44f8c45db013d5e892af5db3314122bd4ba22a004bd64003de55c8a561e3e98e4de2fc6c90cd6ff63", "ad36ae65b0d60df776bd84cb976437ebbe66b1a5c8ebc12958ec67b62113166a"},
    {"661857e3dbd1903488575f89ad46bc914145b55bf62b3278fc9ce9a691f42fb83011", "00c4fe1f581d8c48138c246178b14899bcac98640347a13d28fad5ae9a234a88"},
    {"4942d8d8625f50d3f6fe973e3456ee67f6439be16b3f98e2bd37730141562f0fb28ac3476bc2e5ff17a1fee447d38058", "8a3262616425b9fc15f730fbd74d39abb04bac89812ca41a8c299a703e5e2e61"},
    {"d12efc20aa76955c10f6fca2e52d80558f", "0cddc4a3f09b14c374f7f12ee9b9169e8bde407f46ec85c789c556bd4fbc09a7"},
    {"a9b2a310ea57fca020d5759d", "9daf4a1a21bf3efb018186300e23943d21803707596490578ee7dc69d0ac3b20"},
    {"baa23f3228e6d0c087f19e31baf04d907f5d", "d955f9374fff4141174695791bded97ca9710c2496beee019207d93bc83dd0e0"},
    {"1b8f20c61ef4b5c82aaac6748e5073c2bd8a2e42bc6079746be3c91804ccad713ffaf2daf940ad63bd", "66dbc28bec9a41e79483c96e396c586575c7f6f83c91f50a650c4aa696611646"},
    {"fb89f0f61023de0f133ad0b18deef86337a8861f2dc50cfb76d2f0f4a4ad3e3edda87198c19452f3c8b1dda58d", "044ed06e0272fe15a8f0bb8bf5c817c14880bdd293597d47f1039a4815424f4d"},
    {"279b6543be0a72dda676c5ff99da02f227637b", "f8f7394e8665d30c90870c742363baa529a5053aae1b9438d31c22f5184141a9"},
    {"26d34b5f6d0e23bc1e4fdf11a00d8c", "73b12a2fde6b7d790f7da3eb60f990208f28fabf43380a66cf26b615c7f6f545"},
    {"a475bc116efb92cde208e19af68dd00e28f62e27836d28cc41ff4571391ee21379069e4632599d75", "cc7ef1dd07f26065caeab1a9dbd820db31448812d3cf5d1a592b8b263e493a47"}
}};

hash_result_list sha512_tests{{
    {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
    {"f0d5e1ba902e341a58320a08078af4311e1291dcffd97f00c06988e0e26a071832", "1f23e6ce087e16c4f3585fbe89a4be22961b413076eea1621a81fefaf0c33ecc"},
    {"a5c082e4489c6aa415a961a1e2d0cbf12ed671e5d10d97fb6e63b852b056396670c336d21c75eca4ab0527023b59656a2136", "ad794747682bf286993167ba8b46a0c2b3ad888b91f2917e29832bee1261fcf0"},
    {"c7cbf76a7f875446a32bc8c2a7ce295e1acf85eb10ad66c682b154f08acaa10262ef", "997b848f26a6de7efd214c47f0d56dc95b656ec519ebded493f51c2f5166dbb6"},
    {"2a3333448873620c921c47ae387b1768c7b5227fdb4af5512756a6ba0eab6e84be95da98", "15fbe855e1343185950e6d8b6d907c24e3d8f0d769be537d8b8f239ae33c8926"},
    {"650fb10d5d392f14456bf2f301e8af92bb8a51164b28", "e7abad46a85893bf44e464626473b432ca4e87c94b1e462270ba313d16441bf5"},
    {"0c8fd399", "e2d710db0ccb875f2069683862f743312a5ed223d1e209f5ec27becb9821226a"},
    {"9aa42e8eb0bd", "13ed61ce40d00e1c50573392f16170afd77c43c34211e3f601f044059c3377e3"},
    {"4512b0693593a91b02b06bf0c137", "f0b0c8dfdcc4e31e756a820066e61e383c4159da3278baee23aeb4cfb5add765"},
    {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
    {"98d44f8c45db013d5e892af5db3314122bd4ba22a004bd64003de55c8a561e3e98e4de2fc6c90cd6ff63", "ad36ae65b0d60df776bd84cb976437ebbe66b1a5c8ebc12958ec67b62113166a"},
    {"661857e3dbd1903488575f89ad46bc914145b55bf62b3278fc9ce9a691f42fb83011", "00c4fe1f581d8c48138c246178b14899bcac98640347a13d28fad5ae9a234a88"},
    {"4942d8d8625f50d3f6fe973e3456ee67f6439be16b3f98e2bd37730141562f0fb28ac3476bc2e5ff17a1fee447d38058", "8a3262616425b9fc15f730fbd74d39abb04bac89812ca41a8c299a703e5e2e61"},
    {"d12efc20aa76955c10f6fca2e52d80558f", "0cddc4a3f09b14c374f7f12ee9b9169e8bde407f46ec85c789c556bd4fbc09a7"},
    {"a9b2a310ea57fca020d5759d", "9daf4a1a21bf3efb018186300e23943d21803707596490578ee7dc69d0ac3b20"},
    {"baa23f3228e6d0c087f19e31baf04d907f5d", "d955f9374fff4141174695791bded97ca9710c2496beee019207d93bc83dd0e0"},
    {"1b8f20c61ef4b5c82aaac6748e5073c2bd8a2e42bc6079746be3c91804ccad713ffaf2daf940ad63bd", "66dbc28bec9a41e79483c96e396c586575c7f6f83c91f50a650c4aa696611646"},
    {"fb89f0f61023de0f133ad0b18deef86337a8861f2dc50cfb76d2f0f4a4ad3e3edda87198c19452f3c8b1dda58d", "044ed06e0272fe15a8f0bb8bf5c817c14880bdd293597d47f1039a4815424f4d"},
    {"279b6543be0a72dda676c5ff99da02f227637b", "f8f7394e8665d30c90870c742363baa529a5053aae1b9438d31c22f5184141a9"},
    {"26d34b5f6d0e23bc1e4fdf11a00d8c", "73b12a2fde6b7d790f7da3eb60f990208f28fabf43380a66cf26b615c7f6f545"},
    {"a475bc116efb92cde208e19af68dd00e28f62e27836d28cc41ff4571391ee21379069e4632599d75", "cc7ef1dd07f26065caeab1a9dbd820db31448812d3cf5d1a592b8b263e493a47"}
}};

hash_result_list ripemd_tests{{
    {"", "9c1185a5c5e9fc54612808977ee8f548b2258d31"},
    {"d5c2b51c22c73a03f316c980880a4ce564e80ed716d54d54ddc43181c8f0512617492f37894640940b1184e14d", "306e7d59121745f5d570c5aef029f521276455ce"},
    {"327b8d8ec5d615581e334abdc90dc86f647e0e6e0c136015ef7307d83a2d72", "cc8e4f0af6057cff56cca797216cf312bb47da73"},
    {"d3d9a60e3dc1f5ced2a961786f", "9b7378b66961a4103fa851ee5533acda4bf27b81"},
    {"6416828b23c1327ff88f63", "5ec8f40f77037a5f1c83368111e31921542b485e"},
    {"246f84cfc13b53d4cce6229e6b684e16e2450a411d93", "7da76c22ee062bd6fd59fade9b723a0051fa15ac"},
    {"b772474743eca0d41f94ae40cd57b0f9e64a3d51f2c99e473d78de54bfb398057a", "6acdbcf1ac21be3c6472a83293404ccda2eb06f7"},
    {"a33705b8833a535ada", "cddf70a264a374513a8ad363a55f79d393de75a2"},
    {"5e", "53b92648727c2ec7f961a961786c1cf83540927d"},
    {"ab4c1cc2a9ab7815241a29d95dba37b7f3263befaee248c1614832917c18deff9794", "ff3c8e53be8fa0c02e08abd0e2e370932859c6ba"},
    {"138700cef9f6e79c726e905746d0eb3eab4272380086e35c7772a429f2e99de0e4350eaeab56a8ce8596c286fbf572", "50416b50b8b581b44624efdde7e7ec50680e8718"},
    {"0370b2576696fdf206c9d6ae1581a6217d38", "5b2984f2cec13c2c4626c78f5612884c73df629c"},
    {"822ca89d7ad99c51", "a34b70f1acaabc02ffeea2f88967a5ee1a1b40a4"},
    {"9dbc66f727723493d7d462e5697ead73e0b386d8cbb187b7490e87e53525a3399b604c29", "d969a802332e3be8c8254c5f24cf80e9e000678a"},
    {"", "9c1185a5c5e9fc54612808977ee8f548b2258d31"},
    {"2062a5b9648ee5a70b2523311d6188666671ebb28090ef72061ded0cfe006099cd5546dbf7", "8d699ff496fb01870c7c877c5f883e98329dba8e"},
    {"05a33c8c098c03fb14532eaa9538530b938d3b69782c1a89b2c9166e89cf7772228ea2822f3ef06f0f92bd4adaee109f", "3c467471ee1c19c93d0bb184dd89c86d9b13174d"},
    {"b44a1a6a2a9c9b3e82711225372b0cd60e88bf7be9ced35459ea525da0bb6dfc57117fde2566b2606682", "6ffd7e4188245ba250677b9c0d876e39ebb04c2b"},
    {"4fef1cade9f13670c461b32d70e0549bb966b12680fd0ee40ea33fb4b2948a2bd35e195dfb1f69b5c54fe1f5bb1f0d21d0", "b55f71c9194073973df18691ebec78a7a2c2c6e1"},
    {"b96c28c68798081dafff4f274a78f2cc9e3ba4e332bb", "22f40e4e4921f6d7eccec5cdc269031f3623e912"},
    {"59ce28d8016e7ebb1dedbfef16686735ed65", "0a71887812c3d5c241bcd651a736a0fe9baa86fd"}
}};

pkcs5_pbkdf2_hmac_sha512_result_list pkcs5_pbkdf2_hmac_sha512_tests{{
    {"password", "salt", 1, "867f70cf1ade02cff3752599a3a53dc4af34c7a669815ae5d513554e1c8cf252c02d470a285a0501bad999bfe943c08f050235d7d68b1da55e63f73b60a57fce"},
    {"password", "salt", 2, "e1d9c16aa681708a45f5c7c4e215ceb66e011a2e9f0040713f18aefdb866d53cf76cab2868a39b9f7840edce4fef5a82be67335c77a6068e04112754f27ccf4e"},
    {"password", "salt", 4096, "d197b1b33db0143e018b12f3d1d1479e6cdebdcc97c5c0f87f6902e072f457b5143f30602641b3d55cd335988cb36b84376060ecd532e039b742a239434af2d5"},
    {"passwordPASSWORDpassword", "saltSALTsaltSALTsaltSALTsaltSALTsalt", 4096, "8c0511f4c6e597c6ac6315d8f0362e225f3c501495ba23b868c005174dc4ee71115b59f9e60cd9532fa33e0f75aefe30225c583a186cd82bd4daea9724a3d3b8"},
    {"password", "NaCL", 1, "73decfa58aa2e84f94771a75736bb88bd3c7b38270cfb50cb390ed78b305656af8148e52452b2216b2b8098b761fc6336060a09f76415e9f71ea47f9e9064306"}
}};


#endif
