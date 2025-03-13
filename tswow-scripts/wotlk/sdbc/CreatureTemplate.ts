/*
 * Copyright (C) 2024 tswow <https://github.com/tswow/>
 * and Duskhaven <https://github.com/orgs/Duskhaven-Reforged>
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* tslint:disable */
import { int } from '../../data/primitives'
import { Relation } from '../../data/query/Relations'
import { PrimaryKey } from '../../data/table/PrimaryKey'
import { DBCFloatCell, DBCIntCell, DBCKeyCell, DBCStringCell, DBCUIntCell } from '../../data/dbc/DBCCell'
import { SDBCFile } from './SDBCFile'
import { DBCRow } from '../../data/dbc/DBCRow'
import { SQL_creature_template } from '../sql/creature_template'
import { AttachedScript } from '../std/SmartScript/AttachedScript'
import { SmartScripts } from '../std/SmartScript/SmartScript'

export class CreatureTemplateRow extends DBCRow<CreatureTemplateCreator, CreatureTemplateQuery> {

    @PrimaryKey()
    get entry() { return new DBCKeyCell(this, this.buffer, this.offset + 0) }

    get difficulty_entry_1() { return new DBCUIntCell(this, this.buffer, this.offset + 4) }
    get difficulty_entry_2() { return new DBCUIntCell(this, this.buffer, this.offset + 8) }
    get difficulty_entry_3() { return new DBCUIntCell(this, this.buffer, this.offset + 12) }

    get KillCredit1() { return new DBCUIntCell(this, this.buffer, this.offset + 16) }
    get KillCredit2() { return new DBCUIntCell(this, this.buffer, this.offset + 20) }

    get modelid1() { return new DBCUIntCell(this, this.buffer, this.offset + 24) }
    get modelid2() { return new DBCUIntCell(this, this.buffer, this.offset + 28) }
    get modelid3() { return new DBCUIntCell(this, this.buffer, this.offset + 32) }
    get modelid4() { return new DBCUIntCell(this, this.buffer, this.offset + 36) }

    get name() { return new DBCStringCell(this, this.buffer, this.offset + 40) }

    get subname() { return new DBCStringCell(this, this.buffer, this.offset + 44) }

    get IconName() { return new DBCStringCell(this, this.buffer, this.offset + 48) }

    get gossip_menu_id() { return new DBCUIntCell(this, this.buffer, this.offset + 52) }

    get minlevel() { return new DBCUIntCell(this, this.buffer, this.offset + 56) }

    get maxlevel() { return new DBCUIntCell(this, this.buffer, this.offset + 60) }

    get exp() { return new DBCIntCell(this, this.buffer, this.offset + 64) }

    get faction() { return new DBCUIntCell(this, this.buffer, this.offset + 68) }

    get npcflag() { return new DBCUIntCell(this, this.buffer, this.offset + 72) }

    get speed_walk() { return new DBCFloatCell(this, this.buffer, this.offset + 76) }

    get speed_run() { return new DBCFloatCell(this, this.buffer, this.offset + 80) }

    get scale() { return new DBCFloatCell(this, this.buffer, this.offset + 84) }

    get rank() { return new DBCUIntCell(this, this.buffer, this.offset + 88) }

    get dmgschool() { return new DBCIntCell(this, this.buffer, this.offset + 92) }

    get BaseAttackTime() { return new DBCUIntCell(this, this.buffer, this.offset + 96) }

    get RangeAttackTime() { return new DBCUIntCell(this, this.buffer, this.offset + 100) }

    get BaseVariance() { return new DBCFloatCell(this, this.buffer, this.offset + 104) }

    get RangeVariance() { return new DBCFloatCell(this, this.buffer, this.offset + 108) }

    get unit_class() { return new DBCUIntCell(this, this.buffer, this.offset + 112) }

    get unit_flags() { return new DBCUIntCell(this, this.buffer, this.offset + 116) }

    get unit_flags2() { return new DBCUIntCell(this, this.buffer, this.offset + 120) }

    get dynamicflags() { return new DBCUIntCell(this, this.buffer, this.offset + 124) }

    get family() { return new DBCIntCell(this, this.buffer, this.offset + 128) }

    get type() { return new DBCUIntCell(this, this.buffer, this.offset + 132) }

    get type_flags() { return new DBCUIntCell(this, this.buffer, this.offset + 136) }

    get lootid() { return new DBCUIntCell(this, this.buffer, this.offset + 140) }

    get pickpocketloot() { return new DBCUIntCell(this, this.buffer, this.offset + 144) }

    get skinloot() { return new DBCUIntCell(this, this.buffer, this.offset + 148) }

    get PetSpellDataId() { return new DBCUIntCell(this, this.buffer, this.offset + 152) }

    get VehicleId() { return new DBCUIntCell(this, this.buffer, this.offset + 156) }

    get mingold() { return new DBCUIntCell(this, this.buffer, this.offset + 160) }

    get maxgold() { return new DBCUIntCell(this, this.buffer, this.offset + 164) }

    get AIName() { return new DBCStringCell(this, this.buffer, this.offset + 168) }

    get MovementType() { return new DBCUIntCell(this, this.buffer, this.offset + 172) }

    get HoverHeight() { return new DBCFloatCell(this, this.buffer, this.offset + 176) }

    get HealthModifier() { return new DBCFloatCell(this, this.buffer, this.offset + 180) }

    get ManaModifier() { return new DBCFloatCell(this, this.buffer, this.offset + 184) }

    get ArmorModifier() { return new DBCFloatCell(this, this.buffer, this.offset + 188) }

    get DamageModifier() { return new DBCFloatCell(this, this.buffer, this.offset + 192) }

    get ExperienceModifier() { return new DBCFloatCell(this, this.buffer, this.offset + 196) }

    get RacialLeader() { return new DBCUIntCell(this, this.buffer, this.offset + 200) }

    get movementId() { return new DBCUIntCell(this, this.buffer, this.offset + 204) }

    get RegenHealth() { return new DBCUIntCell(this, this.buffer, this.offset + 208) }

    get mechanic_immune_mask() { return new DBCUIntCell(this, this.buffer, this.offset + 212) }

    get spell_school_immune_mask() { return new DBCUIntCell(this, this.buffer, this.offset + 216) }

    get flags_extra() { return new DBCUIntCell(this, this.buffer, this.offset + 220) }

    get ScriptName() { return new DBCStringCell(this, this.buffer, this.offset + 224) }

    /**
     * Creates a clone of this row with new primary keys.
     *
     * Cloned rows are automatically added at the end of the DBC file.
     */
    clone(ClassID: int, c?: CreatureTemplateCreator): this {
        return this.cloneInternal([ClassID], c);
    }

    //matching std stuff
    get ID() { return this.entry.get() }

    get Scripts() {
        return new AttachedScript(this, () => {
            this.AIName.set('SmartAI');
            return SmartScripts.creature(this.ID);
        })
    }
}

/**
 * Used for object creation (Don't comment these)
 */
export type CreatureTemplateCreator = {
    entry?: int32,
    difficulty_entry_1?: int32,
    difficulty_entry_2?: int32,
    difficulty_entry_3?: int32,
    KillCredit1?: int32,
    KillCredit2?: int32,
    modelid1?: int32,
    modelid2?: int32,
    modelid3?: int32,
    modelid4?: int32,
    name?: string,
    subname?: string,
    IconName?: string,
    gossip_menu_id?: int32,
    minlevel?: int32,
    maxlevel?: int32,
    exp?: int32,
    faction?: int32,
    npcflag?: int32,
    speed_walk?: float,
    speed_run?: float,
    scale?: float,
    rank?: int32,
    dmgschool?: int32,
    BaseAttackTime?: int32,
    RangeAttackTime?: int32,
    BaseVariance?: float,
    RangeVariance?: float,
    unit_class?: int32,
    unit_flags?: int32,
    unit_flags2?: int32,
    dynamicflags?: int32,
    family?: int32,
    type?: int32,
    type_flags?: int32,
    lootid?: int32,
    pickpocketloot?: int32,
    skinloot?: int32,
    PetSpellDataId?: int32,
    VehicleId?: int32,
    mingold?: int32,
    maxgold?: int32,
    AIName?: string,
    MovementType?: int32,
    HoverHeight?: float,
    HealthModifier?: float,
    ManaModifier?: float,
    ArmorModifier?: float,
    DamageModifier?: float,
    ExperienceModifier?: float,
    RacialLeader?: int32,
    movementId?: int32,
    RegenHealth?: int32,
    mechanic_immune_mask?: int32,
    spell_school_immune_mask?: int32,
    flags_extra?: int32,
    ScriptName?: string,
}

/**
 * Used for queries (Don't comment these)
 */
export type CreatureTemplateQuery = {
    entry?: Relation<int32>
    difficulty_entry_1?: Relation<int32>,
    difficulty_entry_2?: Relation<int32>,
    difficulty_entry_3?: Relation<int32>,
    KillCredit1?: Relation<int32>,
    KillCredit2?: Relation<int32>,
    modelid1?: Relation<int32>,
    modelid2?: Relation<int32>,
    modelid3?: Relation<int32>,
    modelid4?: Relation<int32>,
    name?: Relation<string>,
    subname?: Relation<string>,
    IconName?: Relation<string>,
    gossip_menu_id?: Relation<int32>,
    minlevel?: Relation<int32>,
    maxlevel?: Relation<int32>,
    exp?: Relation<int32>,
    faction?: Relation<int32>,
    npcflag?: Relation<int32>,
    speed_walk?: Relation<float>,
    speed_run?: Relation<float>,
    scale?: Relation<float>,
    rank?: Relation<int32>,
    dmgschool?: Relation<int32>,
    BaseAttackTime?: Relation<int32>,
    RangeAttackTime?: Relation<int32>,
    BaseVariance?: Relation<float>,
    RangeVariance?: Relation<float>,
    unit_class?: Relation<int32>,
    unit_flags?: Relation<int32>,
    unit_flags2?: Relation<int32>,
    dynamicflags?: Relation<int32>,
    family?: Relation<int32>,
    type?: Relation<int32>,
    type_flags?: Relation<int32>,
    lootid?: Relation<int32>,
    pickpocketloot?: Relation<int32>,
    skinloot?: Relation<int32>,
    PetSpellDataId?: Relation<int32>,
    VehicleId?: Relation<int32>,
    mingold?: Relation<int32>,
    maxgold?: Relation<int32>,
    AIName?: Relation<string>,//
    MovementType?: Relation<int32>,
    HoverHeight?: Relation<float>,
    HealthModifier?: Relation<float>,
    ManaModifier?: Relation<float>,
    ArmorModifier?: Relation<float>,
    DamageModifier?: Relation<float>,
    ExperienceModifier?: Relation<float>,
    RacialLeader?: Relation<int32>,
    movementId?: Relation<int>,
    RegenHealth?: Relation<int32>,
    mechanic_immune_mask?: Relation<int32>,
    spell_school_immune_mask?: Relation<int32>,
    flags_extra?: Relation<int32>,
    ScriptName?: Relation<string>,
}

export class CreatureTemplateSDBCFile extends SDBCFile<
    CreatureTemplateCreator,
    CreatureTemplateQuery,
    CreatureTemplateRow> {

    constructor() {
        super('CreatureTemplate', (t, b, o) => new CreatureTemplateRow(t, b, o))
    }
    /** Loads a new CreatureTemplate.SDBC from a file. */
    static read(path: string): CreatureTemplateSDBCFile {
        return new CreatureTemplateSDBCFile().read(path)
    }
    add(id: int, c?: CreatureTemplateCreator): CreatureTemplateRow {
        return this.makeRow(0).clone(id, c)
    }
    findByID(id: number) {
        return this.fastSearch(id);
    }

    override getDefaultRows() {
        console.log('Populating CreatureTemplate.sdbc default')
        let rows = []

        SQL_creature_template
            .queryAll({})
            .sort((a, b) => a.entry.get() > b.entry.get() ? 1 : -1)
            .forEach(x => {
                rows.push([
                    x.entry.get(),
                    x.difficulty_entry_1.get(),
                    x.difficulty_entry_2.get(),
                    x.difficulty_entry_3.get(),
                    x.KillCredit1.get(),
                    x.KillCredit2.get(),
                    x.modelid1.get(),
                    x.modelid2.get(),
                    x.modelid3.get(),
                    x.modelid4.get(),
                    x.name.get(),
                    x.subname.get(),
                    x.IconName.get(),
                    x.gossip_menu_id.get(),
                    x.minlevel.get(),
                    x.maxlevel.get(),
                    x.exp.get(),
                    x.faction.get(),
                    x.npcflag.get(),
                    x.speed_walk.get(),
                    x.speed_run.get(),
                    x.scale.get(),
                    x.rank.get(),
                    x.dmgschool.get(),
                    x.BaseAttackTime.get(),
                    x.RangeAttackTime.get(),
                    x.BaseVariance.get(),
                    x.RangeVariance.get(),
                    x.unit_class.get(),
                    x.unit_flags.get(),
                    x.unit_flags2.get(),
                    x.dynamicflags.get(),
                    x.family.get(),
                    x.type.get(),
                    x.type_flags.get(),
                    x.lootid.get(),
                    x.pickpocketloot.get(),
                    x.skinloot.get(),
                    x.PetSpellDataId.get(),
                    x.VehicleId.get(),
                    x.mingold.get(),
                    x.maxgold.get(),
                    x.AIName.get(),
                    x.MovementType.get(),
                    x.HoverHeight.get(),
                    x.HealthModifier.get(),
                    x.ManaModifier.get(),
                    x.ArmorModifier.get(),
                    x.DamageModifier.get(),
                    x.ExperienceModifier.get(),
                    x.RacialLeader.get(),
                    x.movementId.get(),
                    x.RegenHealth.get(),
                    x.mechanic_immune_mask.get(),
                    x.spell_school_immune_mask.get(),
                    x.flags_extra.get(),
                    x.ScriptName.get(),
                ])
            })
        return rows;
    }
}
