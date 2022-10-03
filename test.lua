local proto_ns = Proto.new("nissim", "Nissim53 Protocol")
local SourcePort = ProtoField.uint16("ns.src", "src", base.DEC)
local DestinationPort = ProtoField.uint16("dst.code", "dst", base.DEC)
local Checksum = ProtoField.uint16("ns.checksum", "checksum", base.DEC)
proto_ns.fields = {SourcePort, DestinationPort, Checksum}
function proto_ns.dissector(buffer, pinfo, tree)
    pinfo.cols.protocol = "Nissim53"
    local payload_tree = tree:add( proto_ns, buffer() )
    local src_pos = 1
    local src_len = 1
    local src_buffer = buffer(src_pos,src_len)
    payload_tree:add(SourcePort, src_buffer)
    local dst_pos = src_pos + src_len
    local dst_len = 2
    local dst_buffer = buffer(dst_pos,dst_len)
    payload_tree:add(DestinationPort, dst_buffer)
    local chk_pos = dst_pos + dst_len
    local chk_len = 2
    local chk_buffer = buffer(chk_pos, chk_len)
    payload_tree:add(Checksum, chk_buffer)
end
udp_table = DissectorTable.get("udp.port"):add(55055, proto_ns)